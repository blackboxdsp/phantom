/*
  ==============================================================================

    PhantomOscillator.h
    Created: 20 Jan 2021 21:17:28
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomEnvelopeGenerator.h"

//==============================================================================
/**
*/
class PhantomOscillator 
{
public:
    //==========================================================================
    PhantomOscillator(AudioProcessorValueTreeState&, PhantomEnvelopeGenerator&, PhantomEnvelopeGenerator&);
    ~PhantomOscillator();

    //==========================================================================
    void update(int midiNoteNumber, float sampleRate) noexcept;

    float evaluate() noexcept;

    float midiNoteToFrequency(float midiNote) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscillator)

    //==========================================================================
    void initParameters();
    void initWavetable();

    void updateFrequency() noexcept;
    void updatePhaseDelta() noexcept;
    void updatePhaseDelta(float frequency) noexcept;
    
    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_oscRange;
    std::atomic<float>* p_oscTune;
    std::atomic<float>* p_modDepth;

    //==========================================================================
    Array<float> m_wavetable;
    const int k_wavetableSize = 1 << 11;

    const int k_modExpoThreshold = 5;

    float m_phase = 0.0;
    float m_phaseDelta = 0.0;

    int m_midiNoteNumber;
    float m_frequency;
    float m_sampleRate;

    PhantomEnvelopeGenerator* m_ampEg;
    PhantomEnvelopeGenerator* m_modEg;
};
