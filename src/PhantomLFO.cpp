/*
  ==============================================================================

    PhantomLFO.cpp
    Created: 27 Jan 2021 18:51:41
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLFO.h"

#include "PhantomUtils.h"

//==============================================================================
PhantomLFO::PhantomLFO(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    initParameters();
    resetWavetable();
}

PhantomLFO::~PhantomLFO()
{
    p_rate = nullptr;
    p_shape = nullptr;
}

//==============================================================================
void PhantomLFO::initParameters()
{
    p_rate = m_parameters.getRawParameterValue(Consts::_LFO_RATE_PARAM_ID);
    p_shape = m_parameters.getRawParameterValue(Consts::_LFO_SHAPE_PARAM_ID);
    m_previousShape = *p_shape;
}

void PhantomLFO::resetWavetable() noexcept
{
    m_wavetable.clear();

    for (int i = 0; i < Consts::_WAVETABLE_SIZE; i++)
    {
        float position = (float) i / Consts::_WAVETABLE_SIZE;

        float value;
        switch((int) *p_shape)
        {
            default:
            case 0:
            case 4:
                value = sinf(MathConstants<float>::twoPi * position);
                break;

            case 1:
                value = 2.0f * abs(position * 2.0f - 1.0f) - 1.0f;
                break;

            case 2:
                value = position * 2.0f - 1.0f;
                break;

            case 3:
                value = position <= 0.5f ? 1.0f : -1.0f;
                break;
        }

        m_wavetable.insert(i, value);
    }
}

//==============================================================================
void PhantomLFO::update(float sampleRate) noexcept
{
    m_sampleRate = sampleRate;
    updatePhaseDelta();

    if(*p_shape != m_previousShape)
    {
        resetWavetable();
        m_previousShape = *p_shape;
    }
}

// CAUTION: Remember that the output of this function is in a bipolar numeric format!
float PhantomLFO::evaluate() noexcept
{
    if((int) *p_shape != 4)
        m_sampleValue = m_wavetable[(int) m_phase];
    else
        if((int) m_phase <= 1)
            m_sampleValue = Random::getSystemRandom().nextFloat() * 2.0f - 1.0f;

    m_phase = fmod(m_phase + m_phaseDelta, Consts::_WAVETABLE_SIZE);

    return m_sampleValue;
}

//==============================================================================
void PhantomLFO::updatePhaseDelta() noexcept
{
    float cyclesPerSample = *p_rate / m_sampleRate;
    m_phaseDelta = cyclesPerSample * (float) Consts::_WAVETABLE_SIZE;
}
