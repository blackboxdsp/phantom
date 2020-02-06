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
        // write sinetable
        createSinetable();

        // update all parameters
        attack = parameters.getRawParameterValue("attack");
        decay = parameters.getRawParameterValue("decay");
        sustain = parameters.getRawParameterValue("sustain");
        release = parameters.getRawParameterValue("release");
    }

    ~PhantomVoice() 
    {

    }

    //==========================================================================
    bool canPlaySound(SynthesiserSound* sound) override
    {
        // return if casting sound to my phantom defined sound is successful
        return dynamic_cast<PhantomSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override
    {
        envelope.setSampleRate(getSampleRate());
        envelope.noteOn();

        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        setTableDelta(frequency);

        DBG("NOTE ON:");
        DBG(midiNoteNumber);
        DBG(velocity);
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        clearCurrentNote();

        envelope.noteOff();

        DBG("NOTE OFF:");
        DBG(velocity);
        DBG("");
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
            // read current index of sinetable and increment value accordingly (modulo tableSize)
            auto sampleValue = sinetable[(int) currentTableIndex];
            currentTableIndex = fmod(currentTableIndex + tableDelta, tableSize);

            // apply the envelope
            sampleValue *= envelope.getNextSample();

            for (int channel = 0; channel < buffer.getNumChannels(); channel++)
                buffer.setSample(channel, startSample, sampleValue);

            startSample++;
        }
    }

    //==========================================================================
    void setTableDelta(float frequency)
    {
        auto tableSizeOverSampleRate = (float) tableSize / (float) getSampleRate();
        tableDelta = frequency * tableSizeOverSampleRate;
    }

private:

    //==========================================================================
    void createSinetable()
    {
        sinetable.clear();

        // iterate over table of length tableSize, mapping sine waveform
        for (auto i = 0; i < tableSize; i++)
        {
            auto sample = sinf(MathConstants<float>::twoPi * (float) i / tableSize);
            sinetable.insert(i, sample);
        }
    }

    //==========================================================================
    forcedinline void updateEnvelopeParameters() noexcept
    {
        envelopeParameters.attack   = *attack;
        envelopeParameters.decay    = *decay;
        envelopeParameters.sustain  = powf(2, *sustain / 6);
        envelopeParameters.release  = *release;
    }

    //==========================================================================
    AudioProcessorValueTreeState& parameters;

    // value tree state parameters
    std::atomic<float>* attack;
    std::atomic<float>* decay;
    std::atomic<float>* sustain;
    std::atomic<float>* release;

    // synth envelope variables
    ADSR envelope;
    ADSR::Parameters envelopeParameters;

    // wavetable variables
    Array<float> sinetable;
    float currentTableIndex = 0.0f;
    float frequency = 0.0f;
    float tableDelta = 0.0f;
    const unsigned int tableSize = 1 << 10; // 1024
};