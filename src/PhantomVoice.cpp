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
    m_ampEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::AMP);
    m_phaseEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::PHASE);
    m_filterEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::FLTR);
    m_modEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::MOD);

    m_lfo = new PhantomLFO(m_parameters);

    m_osc01 = new PhantomOscillator(m_parameters, 1);
    m_osc02 = new PhantomOscillator(m_parameters, 2);
    
    m_filter = new PhantomFilter(m_parameters, ps);
}

PhantomVoice::~PhantomVoice()
{
    m_ampEg = nullptr;
    m_phaseEg = nullptr;
    m_filterEg = nullptr;
    m_modEg = nullptr;

    m_lfo = nullptr;
    
    m_osc01 = nullptr;
    m_osc02 = nullptr;

    m_filter = nullptr;
}

//==============================================================================
bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    stopNote(velocity, true);

    m_midiNoteNumber = midiNoteNumber;
    m_osc01->update(m_midiNoteNumber, getSampleRate());
    
    m_ampEg->setSampleRate(getSampleRate());
    m_ampEg->update();
    m_ampEg->noteOn();

    m_phaseEg->setSampleRate(getSampleRate());
    m_phaseEg->update();
    m_phaseEg->noteOn();

    m_filterEg->setSampleRate(getSampleRate());
    m_filterEg->update();
    m_filterEg->noteOn();

    m_modEg->setSampleRate(getSampleRate());
    m_modEg->update();
    m_modEg->noteOn();
}

void PhantomVoice::stopNote(float velocity, bool allowTailOff)
{
    m_ampEg->noteOff();
    m_phaseEg->noteOff();
    m_filterEg->noteOff();
    m_modEg->noteOff();

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
    m_ampEg->update();
    m_phaseEg->update();
    m_filterEg->update();
    m_modEg->update();

    m_lfo->update(getSampleRate());

    m_osc01->update(m_midiNoteNumber, getSampleRate());
    m_filter->update();

    for (int sample = startSample; sample < numSamples; sample++)
    {
        float ampEgMod = m_ampEg->evaluate();
        float phaseEgMod = m_phaseEg->evaluate();
        float filterEgMod = m_filterEg->evaluate();
        float modEgMod = m_modEg->evaluate();

        float lfoMod = m_lfo->evaluate();

        float osc01Value = m_osc01->evaluate(modEgMod, phaseEgMod, lfoMod);
        float filterValue = m_filter->evaluate(osc01Value, filterEgMod, lfoMod);
        float ampValue = filterValue * ampEgMod;

        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            float oldSample = buffer.getSample(channel, sample);
            buffer.setSample(channel, sample, oldSample + ampValue);
        }
    }
}
