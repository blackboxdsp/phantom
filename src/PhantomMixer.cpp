/*
  ==============================================================================

    PhantomMixer.cpp
    Created: 05 Apr 2021 14:11:33
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomMixer.h"
#include "PhantomUtils.h"

PhantomMixer::PhantomMixer(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    m_rng.reset(&Random::Random());

    p_oscBalance = m_parameters.getRawParameterValue(Consts::_MIXER_OSC_BAL_PARAM_ID);
    p_ringMod = m_parameters.getRawParameterValue(Consts::_MIXER_RING_MOD_PARAM_ID);
    p_noise = m_parameters.getRawParameterValue(Consts::_MIXER_NOISE_PARAM_ID);
}

PhantomMixer::~PhantomMixer()
{
    m_rng = nullptr;

    p_oscBalance = nullptr;
    p_ringMod = nullptr;
    p_noise = nullptr;
}

float PhantomMixer::evaluate(float osc01Val, float osc02Val) noexcept
{
    float ringMod = osc01Val * osc02Val * *p_ringMod;

    float random = m_rng->nextFloat() * 2.0f - 1.0f;
    float noise = random * *p_noise;

    return (osc01Val + osc02Val) * 0.5f;
}
