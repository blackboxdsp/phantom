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
    m_phasor = new PhantomPhasor(m_parameters);

    initParameters();
    initWavetable();
}

PhantomOscillator::~PhantomOscillator()
{
    m_phasor = nullptr;

    p_oscRange = nullptr;
    p_oscTune = nullptr;
    p_modDepth = nullptr;

    m_wavetable.clear();
}

//==============================================================================
void PhantomOscillator::initParameters()
{
    p_oscRange = m_parameters.getRawParameterValue(Consts::_OSC_RANGE_PARAM_ID);
    p_oscTune = m_parameters.getRawParameterValue(Consts::_OSC_TUNE_PARAM_ID);
    p_modDepth = m_parameters.getRawParameterValue(Consts::_OSC_MOD_DEPTH_PARAM_ID);
}

void PhantomOscillator::initWavetable()
{
    m_wavetable.clear();

    for (int i = 0; i < Consts::_WAVETABLE_SIZE; i++)
    {
        float value = cosf(MathConstants<float>::twoPi * (float) i / Consts::_WAVETABLE_SIZE);
        m_wavetable.insert(i, value);
    }
}

//==============================================================================
float PhantomOscillator::evaluate(float modEnvelope, float phaseEnvelope) noexcept
{
    float phase = m_phasor->apply(m_phase, phaseEnvelope);
    float sineValue = m_wavetable[(int) phase];

    m_phase = fmod(m_phase + m_phaseDelta, Consts::_WAVETABLE_SIZE);

    float expo = modEnvelope * *p_modDepth * (float) k_modExpoThreshold;
    updatePhaseDelta(m_frequency * std::exp2f(expo));

    return sineValue;
}

//==============================================================================
float PhantomOscillator::midiNoteToFrequency(float midiNote) noexcept
{
    return std::exp((midiNote - 69) * std::log(2) / 12.0) * 440.0;
}

void PhantomOscillator::update(int midiNoteNumber, float sampleRate) noexcept
{
    if(m_midiNoteNumber != midiNoteNumber)
        m_midiNoteNumber = midiNoteNumber;

    m_sampleRate = sampleRate;

    updateFrequency();
    updatePhaseDelta();
}

void PhantomOscillator::updateFrequency() noexcept
{
    float midiNoteFrequency = midiNoteToFrequency(m_midiNoteNumber + *p_oscTune);
    float range = std::exp2f((int) *p_oscRange - 2);
    m_frequency = midiNoteFrequency * range;
}

void PhantomOscillator::updatePhaseDelta() noexcept
{
    updatePhaseDelta(m_frequency);
}

void PhantomOscillator::updatePhaseDelta(float frequency) noexcept
{
    float cyclesPerSample = frequency / m_sampleRate;
    m_phaseDelta = cyclesPerSample * (float) Consts::_WAVETABLE_SIZE;
}