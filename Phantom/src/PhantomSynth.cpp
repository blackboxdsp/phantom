/*
  ==============================================================================

    PhantomSynth.cpp
    Created: 20 Jan 2021 8:59:55pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomSynth.h"

//==============================================================================
PhantomSynth::PhantomSynth()
{

}

PhantomSynth::~PhantomSynth()
{

}

//==============================================================================
bool PhantomSynth::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomSynth::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0)
{    

}

void PhantomSynth::stopNote(float velocity, bool allowTailOff)
{

}

//==============================================================================
void PhantomSynth::pitchWheelMoved(int newPitchWheel)
{

}

void PhantomSynth::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

//==========================================================================
void PhantomSynth::renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    for (int sample = 0; sample < numSamples; sample++)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
            buffer.setSample(channel, startSample, 0.0f);

        startSample++;
    }
}
