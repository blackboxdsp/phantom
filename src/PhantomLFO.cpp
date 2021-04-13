/*
  ==============================================================================

    PhantomLFO.cpp
    Created: 27 Jan 2021 18:51:41
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLFO.h"
#include "PhantomUtils.h"

PhantomLFO::PhantomLFO(AudioProcessorValueTreeState& vts, int lfoNumber, AudioPlayHead* aph)
    :   m_parameters(vts), m_lfoNumber(lfoNumber), m_playHead(aph)
{
    initParameters();
    resetWavetable();

    updateBPM();
}

PhantomLFO::~PhantomLFO()
{
    p_rate = nullptr;
    p_shape = nullptr;

    m_playHead.release();
}

void PhantomLFO::prepareToPlay(int samplesPerBlock, float sampleRate)
{
    m_sampleRate = sampleRate;
    m_samplesPerInterval = 60.0f / m_bpm * m_sampleRate;
}

void PhantomLFO::hiResTimerCallback()
{
    
}

void PhantomLFO::initParameters()
{
    switch(m_lfoNumber)
    {
        default:
        case 1:
            p_rate = m_parameters.getRawParameterValue(Consts::_LFO_01_RATE_PARAM_ID);
            p_shape = m_parameters.getRawParameterValue(Consts::_LFO_01_SHAPE_PARAM_ID);
            break;
        
        case 2:
            p_rate = m_parameters.getRawParameterValue(Consts::_LFO_02_RATE_PARAM_ID);
            p_shape = m_parameters.getRawParameterValue(Consts::_LFO_02_SHAPE_PARAM_ID);
            break;
    }
    
    m_previousShape = *p_shape;
}

void PhantomLFO::resetWavetable() noexcept
{
    m_wavetable.clearQuick();

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

void PhantomLFO::updatePhaseDelta() noexcept
{
    float cyclesPerSample = *p_rate / m_sampleRate;
    m_phaseDelta = cyclesPerSample * (float) Consts::_WAVETABLE_SIZE;
}

void PhantomLFO::updateBPM() noexcept
{
    m_playHead->getCurrentPosition(m_playHeadPositionInfo);
    m_bpm = (float) m_playHeadPositionInfo.bpm;
    DBG(m_bpm << m_playHeadPositionInfo.bpm);
}
