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
    m_waveshaper = new PhantomWaveshaper();

    initParameters();
    initWavetable();
}

PhantomOscillator::~PhantomOscillator()
{
    m_phasor = nullptr;
    m_waveshaper = nullptr;

    p_oscRange = nullptr;
    p_oscCoarseTune = nullptr;
    p_oscFineTune = nullptr;
    p_modDepth = nullptr;
    p_modMode = nullptr;
    p_shapeInt = nullptr;

    m_wavetable.clear();
}

//==============================================================================
void PhantomOscillator::initParameters()
{
    p_oscRange = m_parameters.getRawParameterValue(Consts::_OSC_RANGE_PARAM_ID);
    p_oscCoarseTune = m_parameters.getRawParameterValue(Consts::_OSC_COARSE_TUNE_PARAM_ID);
    p_oscFineTune = m_parameters.getRawParameterValue(Consts::_OSC_FINE_TUNE_PARAM_ID);
    p_modDepth = m_parameters.getRawParameterValue(Consts::_OSC_MOD_DEPTH_PARAM_ID);
    p_modMode = m_parameters.getRawParameterValue(Consts::_OSC_MOD_MODE_PARAM_ID);
    p_shapeInt = m_parameters.getRawParameterValue(Consts::_OSC_SHAPE_INT_PARAM_ID);
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
float PhantomOscillator::evaluate(float modEgMod, float phaseEgMod, float lfoMod) noexcept
{
    float phase = m_phasor->apply(m_phase, phaseEgMod, lfoMod);
    float value = m_wavetable[(int) phase];

    m_phase = fmod(m_phase + m_phaseDelta, Consts::_WAVETABLE_SIZE);

    float mod = (int) *p_modMode ? lfoMod : modEgMod;
    float expo = *p_modDepth * mod * (float) k_modExpoThreshold;
    updatePhaseDelta(m_frequency * std::exp2f(expo));

    float shape = m_waveshaper->atsr(value);
    value = (*p_shapeInt * shape) + ((1.0f - *p_shapeInt) * value);

    return value;
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
    float midiNoteFrequency = midiNoteToFrequency(m_midiNoteNumber + *p_oscCoarseTune + (*p_oscFineTune / 100.0f));
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
