/*
  ==============================================================================

    PhantomFilter.cpp
    Created: 23 Jan 2021 21:22:03
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomFilter.h"
#include "PhantomUtils.h"

PhantomFilter::PhantomFilter(AudioProcessorValueTreeState& vts, dsp::ProcessSpec& ps)
    :   m_parameters(vts)
{
    m_filter.reset(new dsp::StateVariableTPTFilter<float>());
    m_filter->prepare(ps);
    m_filter->setType(dsp::StateVariableTPTFilterType::lowpass);
    m_filter->snapToZero();

    m_waveshaper.reset(new PhantomWaveshaper());

    p_cutoff = m_parameters.getRawParameterValue(Consts::_FLTR_CUTOFF_PARAM_ID);
    p_resonance = m_parameters.getRawParameterValue(Consts::_FLTR_RESO_PARAM_ID);
    p_drive = m_parameters.getRawParameterValue(Consts::_FLTR_DRIVE_PARAM_ID);
    p_type = m_parameters.getRawParameterValue(Consts::_FLTR_MODE_PARAM_ID);
    p_egModDepth = m_parameters.getRawParameterValue(Consts::_FLTR_EG_MOD_DEPTH_PARAM_ID);
    p_lfoModDepth = m_parameters.getRawParameterValue(Consts::_FLTR_LFO_MOD_DEPTH_PARAM_ID);

    update();
}

PhantomFilter::~PhantomFilter()
{
    m_filter = nullptr;
    m_waveshaper = nullptr;

    p_cutoff = nullptr;
    p_resonance = nullptr;
    p_drive = nullptr;
    p_type = nullptr;
    p_egModDepth = nullptr;
    p_lfoModDepth = nullptr;
}

void PhantomFilter::update() noexcept
{
    /**
     * NOTE: Frequency is not being set here because it is called in the update 
     * function. Discontinuous numbers could result in artifacts.
    */

    m_filter->setType((dsp::StateVariableTPTFilterType)(int) *p_type);
    m_filter->setResonance(*p_resonance);
}

float PhantomFilter::evaluate(float sample, float egMod, float lfoMod) noexcept
{
    float envelope = *p_egModDepth * egMod * (abs(*p_lfoModDepth) * -0.5f + 1.0f);
    float lfo = *p_lfoModDepth * (lfoMod * 0.5f + 0.5f) * (abs(*p_egModDepth) * -0.5f + 1.0f);
    float mod = envelope + lfo;
    float offset = k_cutoffModulationMultiplier * mod;

    float frequency = m_waveshaper->clip(*p_cutoff + offset, k_cutoffLowerBounds, k_cutoffUpperCounds);
    m_filter->setCutoffFrequency(frequency);

    float distortion = m_waveshaper->htan(*p_drive, sample);
    sample = (*p_drive * distortion) + ((1.0f - *p_drive) * sample);

    return m_filter->processSample(k_channelNumber, sample);
}
