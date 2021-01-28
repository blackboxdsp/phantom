/*
  ==============================================================================

    PhantomAmplifier.cpp
    Created: 23 Jan 2021 18:23:35
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomAmplifier.h"

#include "PhantomUtils.h"

//==============================================================================
PhantomAmplifier::PhantomAmplifier(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    p_level = m_parameters.getRawParameterValue(Consts::_LEVEL_PARAM_ID);
}

PhantomAmplifier::~PhantomAmplifier()
{
    p_level = nullptr;
}

//==============================================================================
void PhantomAmplifier::apply(AudioBuffer<float>& buffer) noexcept
{
    float gain = powf(2, *p_level / 6);
    if(gain != m_previousGain)
    {
        buffer.applyGainRamp(0, buffer.getNumSamples(), m_previousGain, gain);
        m_previousGain = gain;
    }
    else 
    {
        buffer.applyGain(gain);
    }
}
