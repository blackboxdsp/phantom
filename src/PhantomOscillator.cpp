/*
  ==============================================================================

    PhantomOscillator.cpp
    Created: 20 Jan 2021 21:17:28
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscillator.h"
#include "PhantomUtils.h"

PhantomOscillator::PhantomOscillator(AudioProcessorValueTreeState& vts, int oscNumber)
    : m_parameters(vts), m_oscNumber(oscNumber)
{
    m_phasor.reset(new PhantomPhasor(m_parameters, m_oscNumber));
    m_waveshaper.reset(new PhantomWaveshaper());

    initParameters();
    initWavetable();
}

PhantomOscillator::~PhantomOscillator()
{
    m_phasor.release();
    m_waveshaper.release();

    p_oscRange = nullptr;
    p_oscCoarseTune = nullptr;
    p_oscFineTune = nullptr;
    p_modDepth = nullptr;
    p_modSource = nullptr;
    p_shapeInt = nullptr;

    m_wavetable.clear();
}

void PhantomOscillator::initParameters()
{
    switch(m_oscNumber)
    {
        default:
        case 1:
            p_oscRange = m_parameters.getRawParameterValue(Consts::_OSC_01_RANGE_PARAM_ID);
            p_oscCoarseTune = m_parameters.getRawParameterValue(Consts::_OSC_01_COARSE_TUNE_PARAM_ID);
            p_oscFineTune = m_parameters.getRawParameterValue(Consts::_OSC_01_FINE_TUNE_PARAM_ID);
            p_modDepth = m_parameters.getRawParameterValue(Consts::_OSC_01_MOD_DEPTH_PARAM_ID);
            p_modSource = m_parameters.getRawParameterValue(Consts::_OSC_01_MOD_MODE_PARAM_ID);
            p_shapeInt = m_parameters.getRawParameterValue(Consts::_OSC_01_SHAPE_INT_PARAM_ID);
            break;

        case 2:
            p_oscRange = m_parameters.getRawParameterValue(Consts::_OSC_02_RANGE_PARAM_ID);
            p_oscCoarseTune = m_parameters.getRawParameterValue(Consts::_OSC_02_COARSE_TUNE_PARAM_ID);
            p_oscFineTune = m_parameters.getRawParameterValue(Consts::_OSC_02_FINE_TUNE_PARAM_ID);
            p_modDepth = m_parameters.getRawParameterValue(Consts::_OSC_02_MOD_DEPTH_PARAM_ID);
            p_modSource = m_parameters.getRawParameterValue(Consts::_OSC_02_MOD_MODE_PARAM_ID);
            p_shapeInt = m_parameters.getRawParameterValue(Consts::_OSC_02_SHAPE_INT_PARAM_ID);
            break;
    }
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

float PhantomOscillator::evaluate(float modEgMod, float phaseEgMod, float lfoMod) noexcept
{
    float phase = m_phasor->apply(m_phase, phaseEgMod, lfoMod);
    float value = m_wavetable[(int) phase];

    m_phase = fmod(m_phase + m_phaseDelta, Consts::_WAVETABLE_SIZE);

    float mod = (int) *p_modSource ? lfoMod : modEgMod;
    float expo = *p_modDepth * mod * (float) k_modExpoThreshold;
    updatePhaseDelta(m_frequency * std::exp2f(expo));

    float shape = m_waveshaper->atsr(value);
    value = (*p_shapeInt * shape) + ((1.0f - *p_shapeInt) * value);

    return value;
}

float PhantomOscillator::midiNoteToFrequency(float midiNote) noexcept
{
    return std::exp((midiNote - 69) * std::log(2) / 12.0f) * 440.0f;
}

void PhantomOscillator::update(int midiNoteNumber, float sampleRate) noexcept
{
    if(m_midiNoteNumber != midiNoteNumber)
        m_midiNoteNumber = midiNoteNumber;

    m_sampleRate = sampleRate;

    updateFrequency();
    updatePhaseDelta();
}

void PhantomOscillator::updatePhase(float phase) noexcept
{
    m_phase = phase;
}

float PhantomOscillator::readPhase() noexcept
{
    return m_phase;
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
