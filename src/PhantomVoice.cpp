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
PhantomVoice::PhantomVoice(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    p_oscillatorTune = m_parameters.getRawParameterValue("oscillatorTune");

    m_oscillator = new PhantomOscillator();
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
    m_frequency = midiNoteToFrequency(midiNoteNumber + *p_oscillatorTune);
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

//==========================================================================
float PhantomVoice::midiNoteToFrequency(float midiNote)
{
    return std::exp((midiNote - 69) * std::log(2) / 12.0) * 440.0;
}
