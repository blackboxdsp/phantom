/*
  ==============================================================================

    PhantomVoice.cpp
    Created: 20 Jan 2021 8:59:55pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomVoice.h"

#include "PhantomSound.h"
#include "PhantomUtils.h"

//==============================================================================
PhantomVoice::PhantomVoice(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    p_oscRange = m_parameters.getRawParameterValue(Parameters::_OSC_RANGE_PARAM_ID);
    p_oscTune = m_parameters.getRawParameterValue(Parameters::_OSC_TUNE_PARAM_ID);
    m_osc = new PhantomOscillator();

    char* ampEgParams[] = {
        Parameters::_AMP_EG_ATK_PARAM_ID,
        Parameters::_AMP_EG_DEC_PARAM_ID,
        Parameters::_AMP_EG_SUS_PARAM_ID,
        Parameters::_AMP_EG_REL_PARAM_ID
    };
    m_ampEg = new PhantomEnvelopeGenerator(m_parameters, ampEgParams);
}

PhantomVoice::~PhantomVoice()
{
    m_osc = nullptr;
    p_oscTune = nullptr;
    p_oscRange = nullptr;

    m_ampEg = nullptr;
}

//==============================================================================
bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{ 
    m_midiNoteNumber = midiNoteNumber;
    updateOscillator();
    
    m_ampEg->setSampleRate(getSampleRate());
    m_ampEg->update();
    m_ampEg->noteOn();
}

void PhantomVoice::stopNote(float velocity, bool allowTailOff)
{
    m_ampEg->noteOff();

    clearCurrentNote();
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
    updateOscillator();
    m_ampEg->update();

    for (int sample = 0; sample < numSamples; sample++)
    {
        float value = m_osc->getNextSample() * m_ampEg->getNextSample();

        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
            buffer.setSample(channel, startSample, value);

        startSample++;
    }
}

//==============================================================================
float PhantomVoice::midiNoteToFrequency(float midiNote)
{
    return std::exp((midiNote - 69) * std::log(2) / 12.0) * 440.0;
}

//==============================================================================
forcedinline void PhantomVoice::updateOscillator() noexcept
{
    float midiNoteFrequency = midiNoteToFrequency(m_midiNoteNumber + *p_oscTune);
    float range = std::exp2f((int)*p_oscRange - 2);
    float frequency = midiNoteFrequency * range;

    m_osc->setPhaseDelta(frequency, getSampleRate());
}
