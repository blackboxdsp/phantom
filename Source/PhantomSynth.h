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
        : parameters(vts)
    {
        // write sinetable
        createSinetable();

        // update all parameters
        level = parameters.getRawParameterValue("level");
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
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        setFrequency(frequency);

        DBG("NOTE ON:");
        DBG(midiNoteNumber);
        DBG(velocity);
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        clearCurrentNote();

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
        for (int sample = 0; sample < numSamples; sample++)
        {
            for (int channel = 0; channel < buffer.getNumChannels(); channel++)
            {
                auto gain = powf(2, *level / 6);
                auto currentSample = sinetable[(int) currentTableIndex] * gain;

                // keep table index wrapped around table size
                currentTableIndex = fmod(currentTableIndex + tableDelta, tableSize);
                
                buffer.addSample(channel, startSample, currentSample);
            }
            startSample++;
        }
    }

    //==========================================================================
    void setFrequency(float frequency)
    {
        auto tableSizeOverSampleRate = (float) tableSize / (float) getSampleRate();
        tableDelta = frequency * tableSizeOverSampleRate;
    }

private:

    //==========================================================================
    void createSinetable()
    {
        sinetable.clear();
        for (auto i = 0; i < tableSize; i++)
        {
            auto sample = sinf(MathConstants<float>::twoPi * (float) i / tableSize);
            sinetable.insert(i, sample);
        }
    }

    //==========================================================================
    AudioProcessorValueTreeState& parameters;

    // parameters
    float* level;

    // wavetable variables
    Array<float> sinetable;
    float currentTableIndex = 0.0f;
    float frequency = 0.0f;
    float tableDelta = 0.0f;
    const unsigned int tableSize = 1 << 10; // 1024 - 1
};