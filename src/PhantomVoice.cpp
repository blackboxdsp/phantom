/*
  ==============================================================================

    PhantomVoice.cpp
    Created: 20 Jan 2021 20:59:55
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomVoice.h"

#include "PhantomSound.h"
#include "PhantomUtils.h"

//==============================================================================
PhantomVoice::PhantomVoice(AudioProcessorValueTreeState& vts, dsp::ProcessSpec& ps)
    :   m_parameters(vts)
{
    m_osc = new PhantomOscillator(m_parameters);
    m_filter = new PhantomFilter(m_parameters, ps);
    m_ampEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::AMP);
    m_amp = new PhantomAmplifier(m_parameters);
}

PhantomVoice::~PhantomVoice()
{
    m_osc = nullptr;
    m_filter = nullptr;
    m_ampEg = nullptr;
    m_amp = nullptr;
}

//==============================================================================
bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{ 
    m_midiNoteNumber = midiNoteNumber;
    m_osc->update(m_midiNoteNumber, getSampleRate());
    
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
    m_osc->update(m_midiNoteNumber, getSampleRate());
    m_filter->update();
    m_ampEg->update();

    for (int sample = startSample; sample < numSamples; sample++)
    {
        float postOsc = m_osc->getNextSample() * m_ampEg->getNextSample();

        float postFilter = m_filter->evaluate(postOsc);

        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
            buffer.setSample(channel, sample, postFilter);
    }

    m_amp->apply(buffer);
}
