/*
  ==============================================================================

    PhantomVoice.cpp
    Created: 20 Jan 2021 8:59:55pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomVoice.h"

#include "PhantomSound.h"

//==============================================================================
PhantomVoice::PhantomVoice()
{
    m_oscillator = new PhantomOscillator();

    m_frequency = 220.0;
}

PhantomVoice::~PhantomVoice()
{
    m_oscillator = nullptr;
}

//==============================================================================
bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{    
    m_frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    m_oscillator->setPhaseDelta(m_frequency, getSampleRate());
}

void PhantomVoice::stopNote(float velocity, bool allowTailOff)
{

}

//==============================================================================
void PhantomVoice::pitchWheelMoved(int newPitchWheel)
{

}

void PhantomVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

//==============================================================================
void PhantomVoice::renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    m_oscillator->setPhaseDelta(m_frequency, getSampleRate());

    for (int sample = 0; sample < numSamples; sample++)
    {
        float value = m_oscillator->evaluate() * 0.3f;

        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
            buffer.setSample(channel, startSample, value);

        startSample++;
    }
}
