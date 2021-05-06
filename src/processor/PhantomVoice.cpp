/*
  ==============================================================================

    PhantomVoice.cpp
    Created: 20 Jan 2021 20:59:55
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomVoice.h"

#include "PhantomSound.h"
#include "../utils/PhantomUtils.h"

PhantomVoice::PhantomVoice(AudioProcessorValueTreeState& vts, dsp::ProcessSpec& ps) : m_parameters(vts)
{
    p_oscSync = m_parameters.getRawParameterValue(Consts::_OSC_SYNC_PARAM_ID);
    
    m_ampEnv.reset(new PhantomEnvelope(m_parameters, EnvelopeType::AMP));
    m_phaseEnv.reset(new PhantomEnvelope(m_parameters, EnvelopeType::PHASE));
    m_filterEnv.reset(new PhantomEnvelope(m_parameters, EnvelopeType::FLTR));
    m_modEnv.reset(new PhantomEnvelope(m_parameters, EnvelopeType::MOD));

    m_lfo01.reset(new PhantomLFO(m_parameters, 1));
    m_lfo02.reset(new PhantomLFO(m_parameters, 2));

    m_primaryOsc.reset(new PhantomOscillator(m_parameters, 1));
    m_secondaryOsc.reset(new PhantomOscillator(m_parameters, 2));
    m_mixer.reset(new PhantomMixer(m_parameters));

    m_filter.reset(new PhantomFilter(m_parameters, ps));
}

PhantomVoice::~PhantomVoice()
{
    p_oscSync = nullptr;

    m_ampEnv = nullptr;
    m_phaseEnv = nullptr;
    m_filterEnv = nullptr;
    m_modEnv = nullptr;

    m_lfo01 = nullptr;
    m_lfo02 = nullptr;
    
    m_primaryOsc = nullptr;
    m_secondaryOsc = nullptr;
    
    m_mixer = nullptr;

    m_filter = nullptr;
}

bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    m_isNoteOn = true;
    m_isNoteCleared = false;

    const float sampleRate = (float) getSampleRate();

    m_midiNoteNumber = midiNoteNumber;
    m_primaryOsc->update(m_midiNoteNumber, sampleRate);
    m_secondaryOsc->update(m_midiNoteNumber, sampleRate);

    m_ampEnv->noteOn();
    m_phaseEnv->noteOn();
    m_filterEnv->noteOn();
    m_modEnv->noteOn();
}

void PhantomVoice::stopNote(float velocity, bool allowTailOff)
{
    if(!allowTailOff)
    {
        clear();
        return;
    }

    DBG("Note OFF!" << " ... " << velocity);

    m_isNoteOn = false;

    m_ampEnv->noteOff();
    m_phaseEnv->noteOff();
    m_filterEnv->noteOff();
    m_modEnv->noteOff();
}

void PhantomVoice::clear()
{
    clearCurrentNote();

    m_ampEnv->reset();
    m_phaseEnv->reset();
    m_filterEnv->reset();
    m_modEnv->reset();

    m_primaryOsc->reset();
    m_secondaryOsc->reset();

    m_isNoteCleared = true;
}

void PhantomVoice::renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    if(numSamples == 0) return;

    if(m_isNoteOn && !isKeyDown())
        stopNote(0.0f, true);

    const float sampleRate = (float) getSampleRate();

    m_ampEnv->update(sampleRate);
    m_phaseEnv->update(sampleRate);
    m_filterEnv->update(sampleRate);
    m_modEnv->update(sampleRate);

    m_lfo01->update(sampleRate);
    m_lfo02->update(sampleRate);

    m_primaryOsc->update(m_midiNoteNumber, sampleRate);
    m_secondaryOsc->update(m_midiNoteNumber, sampleRate);
    
    m_filter->update();

    for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
    {
        float ampEnvMod = m_ampEnv->evaluate();
        float phaseEnvMod = m_phaseEnv->evaluate();
        float filterEnvMod = m_filterEnv->evaluate();
        float modEnvMod = m_modEnv->evaluate();

        float lfo01Mod = m_lfo01->evaluate();
        float lfo02Mod = m_lfo02->evaluate();

        handleOscSync(m_primaryOsc->readPhase());

        float primaryOscVal = m_primaryOsc->evaluate(modEnvMod, lfo02Mod, phaseEnvMod, lfo02Mod);
        float secondaryOscVal = m_secondaryOsc->evaluate(modEnvMod, lfo02Mod, phaseEnvMod, lfo02Mod);
        float oscVal = m_mixer->evaluate(primaryOscVal, secondaryOscVal);

        float filterVal = m_filter->evaluate(oscVal, filterEnvMod, lfo01Mod);
        float ampVal = filterVal * ampEnvMod;

        if(isVoiceActive()) m_tailOff = 1.0f;
        float finalVal = ampVal * m_tailOff;

        m_tailOff *= 0.99f;
        if(!m_isNoteCleared && m_tailOff < 0.001f)
            clear();

        for (int channelIdx = 0; channelIdx < buffer.getNumChannels(); channelIdx++)
            buffer.addSample(channelIdx, sampleIdx + startSample, finalVal);
    }
}

void PhantomVoice::handleOscSync(const float valueToRead) noexcept
{
    if(!*p_oscSync) return;

    if(valueToRead <= k_oscSyncPhaseThreshold)
        m_secondaryOsc->updatePhase(valueToRead);
}
