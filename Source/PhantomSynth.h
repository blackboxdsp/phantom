/*
  ==============================================================================

    PhantomVoice.h
    Created: 1 Feb 2020 8:35:21am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class PhantomSound : public SynthesiserSound
{
public:
    //==========================================================================
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }
    bool appliesToChannel(int midiChannel) override
    {
        return true;
    }
};

//==============================================================================
class PhantomVoice : public SynthesiserVoice
{
public:
    //==========================================================================
    PhantomVoice(AudioProcessorValueTreeState& vts)
        : parameters(vts), envelope()
    {
        // update phase distortion parameters
        phaseId = parameters.getRawParameterValue("phaseId");

        // update adsr parameters
        attack = parameters.getRawParameterValue("attack");
        decay = parameters.getRawParameterValue("decay");
        sustain = parameters.getRawParameterValue("sustain");
        release = parameters.getRawParameterValue("release");
    }

    ~PhantomVoice() {};

    //==========================================================================
    bool canPlaySound(SynthesiserSound* sound) override
    {
        // return if casting sound to my phantom defined sound is successful
        return dynamic_cast<PhantomSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override
    {
        setPhaseDelta(MidiMessage::getMidiNoteInHertz(midiNoteNumber));

        envelope.setSampleRate(getSampleRate());
        envelope.noteOn();
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        envelope.noteOff();
        clearCurrentNote();
    }

    //==========================================================================
    void pitchWheelMoved(int newPitchWheel)                             override {}
    void controllerMoved(int controllerNumber, int newControllerValue)  override {}

    //==========================================================================
    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
    {
        // first update adsr parameters struct and pass to envelope
        updateEnvelopeParameters();
        envelope.setParameters(envelopeParameters);

        // processing loop for samples
        for (int sample = 0; sample < numSamples; sample++)
        {
            updatePhasor();
            
            auto sampleValue = cosf(phasor);

            sampleValue *= envelope.getNextSample();

            for (int channel = 0; channel < buffer.getNumChannels(); channel++)
                buffer.setSample(channel, startSample, sampleValue);

            startSample++;
        }
    }

private:

    //==========================================================================
    forcedinline void updateEnvelopeParameters() noexcept
    {
        envelopeParameters.attack   = *attack;
        envelopeParameters.decay    = *decay;
        envelopeParameters.sustain  = powf(2, *sustain / 6);
        envelopeParameters.release  = *release;
    }

    //==========================================================================
    forcedinline void updatePhasor() noexcept
    {        
        // get current position in float from 0.0f to 1.0f
        auto currentPosition = phasePosition / MathConstants<float>::twoPi;

        // update phaseOffset according to DCW envelope (see Casio CZ-101 manual)
        phaseOffset = envelope.getNextSample() * -0.5f + 0.5f;

        switch ((int) *phaseId)
        {
            // SAWTOOTH WAVE
            default:
            case 0:
                if (currentPosition < phaseOffset)
                {
                    float m1 = 0.5f / phaseOffset;
                    phasor = m1 * currentPosition;
                }
                else
                {
                    float m2 = 0.5f / (1.0f - phaseOffset);
                    float b2 = 1.0f - m2;
                    phasor = m2 * currentPosition + b2;
                }
        }

        phasor *= MathConstants<float>::twoPi;

        phasePosition = fmod(phasePosition + phaseDelta, MathConstants<float>::twoPi);
    }

    void setPhaseDelta(float frequency)
    {
        auto cyclesPerSample = frequency / (float) getSampleRate();
        phaseDelta = cyclesPerSample * MathConstants<float>::twoPi;
    }

    //==========================================================================
    AudioProcessorValueTreeState& parameters;

    // phase distortion parameters
    std::atomic<float>* phaseId;

    // phase distortion variables
    float phasor = 0.0f;
    float phaseDelta = 0.0f;
    float phaseOffset = 0.5f;
    float phasePosition = 0.0f;

    // ADSR parameters
    std::atomic<float>* attack;
    std::atomic<float>* decay;
    std::atomic<float>* sustain;
    std::atomic<float>* release;

    // synth variables
    ADSR envelope;
    ADSR::Parameters envelopeParameters;
};