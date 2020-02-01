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
        // return if casting sound to my phantom defined sound is successful
        return dynamic_cast<PhantomSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        DBG(midiNoteNumber);
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        clearCurrentNote();
    }

    //==========================================================================

    void pitchWheelMoved(int newPitchWheel)                             override {}
    void controllerMoved(int controllerNumber, int newControllerValue)  override {}

    //==========================================================================

    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
    {

    }

private:
    double frequency;
    double level;

};