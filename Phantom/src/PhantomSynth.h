/*
  ==============================================================================

    PhantomSynth.h
    Created: 20 Jan 2021 8:59:55pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomOscillator.h"

//==============================================================================
/**
*/
class PhantomSound : public SynthesiserSound
{
public:
    //==========================================================================
    bool appliesToNote(int midiNoteNumber) override 
    {
        return true;
    }
    
    bool appliesToChannel(int midiChannelNumber) override 
    {
        return true;
    }

};

class PhantomVoice : public SynthesiserVoice
{
public:
    //==========================================================================
    PhantomVoice();
    ~PhantomVoice();

    //==========================================================================
    bool canPlaySound(SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override;

    void stopNote(float velocity, bool allowTailOff) override;

    //==========================================================================
    void pitchWheelMoved(int newPitchWheel) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    //==========================================================================
    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples) override;

private:
    //==========================================================================
    PhantomOscillator* oscillator;
};

