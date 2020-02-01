/*
  ==============================================================================

    PhantomVoice.h
    Created: 1 Feb 2020 8:35:21am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./PhantomSound.h"

//==============================================================================
class PhantomVoice : public SynthesiserVoice
{
public:
    //==========================================================================
    PhantomVoice()
    {
        createSinetable();
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
                auto currentSample = sinetable[(int) currentTableIndex];
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
    // parameters
    float frequency = 0.0f;
    float level = 0.5f;

    // wavetable variables
    Array<float> sinetable;
    float currentTableIndex = 0.0f;
    float tableDelta = 0.0f;
    const unsigned int tableSize = 1 << 10; // 1024 - 1
};