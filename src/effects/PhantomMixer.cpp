/*
  ==============================================================================

    PhantomMixer.cpp
    Created: 05 Apr 2021 14:11:33
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomMixer.h"

#include "../utils/PhantomUtils.h"

PhantomMixer::PhantomMixer(AudioProcessorValueTreeState& vts) : m_parameters(vts)
{
    m_rng.reset(new Random());

    p_oscBalance = m_parameters.getRawParameterValue(Consts::_MIXER_OSC_BAL_PARAM_ID);
    p_ampGain = m_parameters.getRawParameterValue(Consts::_MIXER_AMP_GAIN_PARAM_ID);
    p_ringMod = m_parameters.getRawParameterValue(Consts::_MIXER_RING_MOD_PARAM_ID);
    p_noise = m_parameters.getRawParameterValue(Consts::_MIXER_NOISE_PARAM_ID);
}

PhantomMixer::~PhantomMixer()
{
    m_rng = nullptr;

    p_oscBalance = nullptr;
    p_ampGain = nullptr;
    p_ringMod = nullptr;
    p_noise = nullptr;
}

float PhantomMixer::evaluate(float osc01Val, float osc02Val) noexcept
{
    float osc = osc01Val * (1.0f - *p_oscBalance) + osc02Val * *p_oscBalance;

    float ringMod = osc01Val * osc02Val * *p_ringMod;

    float random = (m_rng->nextFloat() + m_previousNoise) / 2.0f;
    float noise = (random * 2.0f - 1.0f) * *p_noise;
    m_previousNoise = random;

    float mixed = (osc + osc + ringMod + noise) / std::sqrtf(3.0f);

    return mixed * *p_ampGain;
}
