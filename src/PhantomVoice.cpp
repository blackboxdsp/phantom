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

    m_primaryOsc.reset(new PhantomOscillator(m_parameters, 1));
    m_secondaryOsc.reset(new PhantomOscillator(m_parameters, 2));
    p_oscSync = m_parameters.getRawParameterValue(Consts::_OSC_SYNC_PARAM_ID);
    m_mixer.reset(new PhantomMixer(m_parameters));

    m_filter = new PhantomFilter(m_parameters, ps);
}

PhantomVoice::~PhantomVoice()
{
    m_ampEg = nullptr;
    m_phaseEg = nullptr;
    m_filterEg = nullptr;
    m_modEg = nullptr;

    m_lfo = nullptr;
    
    m_primaryOsc.release();
    m_secondaryOsc.release();
    p_oscSync = nullptr;
    m_mixer.release();

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
    m_primaryOsc->update(m_midiNoteNumber, getSampleRate());
    m_secondaryOsc->update(m_midiNoteNumber, getSampleRate());
    
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

    m_primaryOsc->update(m_midiNoteNumber, getSampleRate());
    m_secondaryOsc->update(m_midiNoteNumber, getSampleRate());
    
    m_filter->update();

    for (int sample = startSample; sample < numSamples; sample++)
    {
        float ampEgMod = m_ampEg->evaluate();
        float phaseEgMod = m_phaseEg->evaluate();
        float filterEgMod = m_filterEg->evaluate();
        float modEgMod = m_modEg->evaluate();

        float lfoMod = m_lfo->evaluate();

        float primaryOscVal = m_primaryOsc->evaluate(modEgMod, phaseEgMod, lfoMod);
        float secondaryOscVal = m_secondaryOsc->evaluate(modEgMod, phaseEgMod, lfoMod);
        float oscVal = (primaryOscVal + secondaryOscVal) / 2.0f;

        if(*p_oscSync)
            handleOscSync(primaryOscVal);

        float filterVal = m_filter->evaluate(oscVal, filterEgMod, lfoMod);
        float ampVal = filterVal * ampEgMod;

        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            float oldSample = buffer.getSample(channel, sample);
            buffer.setSample(channel, sample, oldSample + ampVal);
        }
    }
}

void PhantomVoice::handleOscSync(float valueToRead) noexcept
{
    if(std::abs(valueToRead) <= k_oscSyncPhaseThreshold) {
        if(m_oscSyncToggle)
            m_secondaryOsc->updatePhase(valueToRead);

        m_oscSyncToggle = !m_oscSyncToggle;
    }
}
