/*
  ==============================================================================

    PhantomOscillator.cpp
    Created: 20 Jan 2021 21:17:28
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscillator.h"

#include "PhantomUtils.h"

//==========================================================================
PhantomOscillator::PhantomOscillator(AudioProcessorValueTreeState& vts)
    : m_parameters(vts)
{
    initParameters();
    initWavetable();
}

PhantomOscillator::~PhantomOscillator()
{
    p_oscRange = nullptr;
    p_oscTune = nullptr;

    m_wavetable.clear();
}

//==============================================================================
float PhantomOscillator::evaluate()
{
    float value = m_wavetable[(int) m_phase];

    m_phase = fmod(m_phase + m_phaseDelta, k_wavetableSize);

    return value;
}

//==============================================================================
void PhantomOscillator::initParameters()
{
    p_oscRange = m_parameters.getRawParameterValue(Params::_OSC_RANGE_PARAM_ID);
    p_oscTune = m_parameters.getRawParameterValue(Params::_OSC_TUNE_PARAM_ID);
}

void PhantomOscillator::initWavetable()
{
    m_wavetable.clear();

    for (int i = 0; i < k_wavetableSize; i++)
    {
        float value = cosf(MathConstants<float>::twoPi * (float) i / k_wavetableSize);
        m_wavetable.insert(i, value);
    }
}

//==============================================================================
float PhantomOscillator::midiNoteToFrequency(float midiNote)
{
    return std::exp((midiNote - 69) * std::log(2) / 12.0) * 440.0;
}

void PhantomOscillator::update(int midiNoteNumber, float sampleRate)
{
    if(m_midiNoteNumber != midiNoteNumber)
        m_midiNoteNumber = midiNoteNumber;

    m_sampleRate = sampleRate;

    updateFrequency();
    updatePhaseDelta();
}

void PhantomOscillator::updateFrequency()
{
    float midiNoteFrequency = midiNoteToFrequency(m_midiNoteNumber + *p_oscTune);
    float range = std::exp2f((int) *p_oscRange - 2);
    m_frequency = midiNoteFrequency * range;
}

void PhantomOscillator::updatePhaseDelta()
{
    float cyclesPerSample = m_frequency / m_sampleRate;
    m_phaseDelta = cyclesPerSample * (float) k_wavetableSize;
}
