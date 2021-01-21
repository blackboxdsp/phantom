/*
  ==============================================================================

    PhantomOscillator.cpp
    Created: 20 Jan 2021 9:17:28pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscillator.h"

//==========================================================================
PhantomOscillator::PhantomOscillator()
{
    initWavetable();
}

PhantomOscillator::~PhantomOscillator()
{
    clearWavetable();
}

//==============================================================================
void PhantomOscillator::initWavetable()
{
    clearWavetable();

    for (int i = 0; i < k_wavetableSize; i++)
    {
        float value = cosf(MathConstants<float>::twoPi * (float) i / k_wavetableSize);
        m_wavetable.insert(i, value);
    }
}

void PhantomOscillator::clearWavetable()
{
    m_wavetable.clear();
}

//==============================================================================
void PhantomOscillator::setPhaseDelta(float frequency, float sampleRate)
{
    float cyclesPerSample = frequency / sampleRate;
    m_phaseDelta = cyclesPerSample * (float) k_wavetableSize;
}

//==============================================================================
float PhantomOscillator::evaluate()
{
    float value = m_wavetable[(int) m_phase];

    m_phase = fmod(m_phase + m_phaseDelta, k_wavetableSize);

    return value;
}
