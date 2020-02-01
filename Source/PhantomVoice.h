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
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return true;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override
    {

    }

    void stopNote(float velocity, bool allowTailOff) override
    {

    }

    //==========================================================================

    void pitchWheelMoved(int newPitchWheel)                             override {}
    void controllerMoved(int controllerNumber, int newControllerValue)  override {}

    //==========================================================================

    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
    {

    }

private:

};