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

    p_cutoff = m_parameters.getRawParameterValue(Params::_FLTR_CUTOFF_PARAM_ID);
    p_resonance = m_parameters.getRawParameterValue(Params::_FLTR_RESO_PARAM_ID);
    update();
}

PhantomFilter::~PhantomFilter()
{
    m_filter = nullptr;
}

//==============================================================================
void PhantomFilter::update()
{
    m_filter->setCutoffFrequency(*p_cutoff);
    m_filter->setResonance(*p_resonance);
}

//==============================================================================
float PhantomFilter::evaluate(float sample)
{
    return m_filter->processSample(0, sample);
}
