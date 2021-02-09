/*
  ==============================================================================

    PhantomFilter.h
    Created: 23 Jan 2021 21:22:03
    Author:  Matthew Maxwell

    ** This filter implementation was taken from 

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomWaveshaper.h"

//==============================================================================
/**
*/
class PhantomFilter
{
public:
    //==========================================================================
    PhantomFilter(AudioProcessorValueTreeState&, dsp::ProcessSpec&);
    ~PhantomFilter();

    //==========================================================================
    void update() noexcept;

    //==========================================================================
    float evaluate(float sample, float egMod, float lfoMod) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomFilter)

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_cutoff;
    std::atomic<float>* p_resonance;
    std::atomic<float>* p_drive;
    std::atomic<float>* p_egModDepth;
    std::atomic<float>* p_lfoModDepth;

    float m_previousFrequency;

    const int k_channelNumber = 0;
    const float k_cutoffModulationMultiplier = 3000.0f;
    const float k_cutoffLowerBounds = 0.0f;
    const float k_cutoffUpperCounds = 11000.0f;

    //==========================================================================
    dsp::StateVariableTPTFilter<float>* m_filter;

    PhantomWaveshaper* m_waveshaper;
};
