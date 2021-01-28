/*
  ==============================================================================

    PhantomFilter.cpp
    Created: 23 Jan 2021 21:22:03
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomFilter.h"

#include "PhantomUtils.h"

//==============================================================================
PhantomFilter::PhantomFilter(AudioProcessorValueTreeState& vts, dsp::ProcessSpec& ps)
    :   m_parameters(vts)
{
    m_filter = new dsp::StateVariableTPTFilter<float>();
    m_filter->prepare(ps);
    m_filter->setType(m_type);
    m_filter->snapToZero();

    p_cutoff = m_parameters.getRawParameterValue(Consts::_FLTR_CUTOFF_PARAM_ID);
    p_resonance = m_parameters.getRawParameterValue(Consts::_FLTR_RESO_PARAM_ID);
    p_modDepth = m_parameters.getRawParameterValue(Consts::_FLTR_MOD_DEPTH_PARAM_ID);

    update();
}

PhantomFilter::~PhantomFilter()
{
    m_filter = nullptr;

    p_cutoff = nullptr;
    p_resonance = nullptr;
    p_modDepth = nullptr;
}

//==============================================================================
void PhantomFilter::update() noexcept
{
    // NOTE: Frequency is not being set here because it is called in the update 
    // function. Discontinuous numbers could result in artifacts.
    m_filter->setResonance(*p_resonance);
}

//==============================================================================
float PhantomFilter::evaluate(float sample, float envelope, float lfo) noexcept
{
    float egOffset = k_cutoffModulationMultiplier * envelope * *p_modDepth;
    float offset = k_cutoffModulationMultiplier * envelope * *p_modDepth * lfo;
    float frequency = clip(*p_cutoff + offset, k_cutoffLowerBounds, k_cutoffUpperCounds);
    m_filter->setCutoffFrequency(frequency);

    return m_filter->processSample(k_channelNumber, sample);
}

float PhantomFilter::clip(float n, float lower, float upper) noexcept
{
    return std::max(lower, std::min(n, upper));
}
