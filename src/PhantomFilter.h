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
    float clip(float n, float lower, float upper) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomFilter)

    //==========================================================================
    // NOTE: These functions are non-linear processing functions to give the 
    // filter a nice drive feature. They are in order of increasing intensity.
    // The function with an asterisk in the comment is currently being used.

    float fexp2(float x) noexcept;      // Fuzz Exponential 2
    float atsr(float x) noexcept;       // Arctangent Square Root
    float cube(float x) noexcept;       // Cube
    float htan(float x) noexcept;       // Hyperbolic Tangent*
    float hclip(float x) noexcept;      // Hard Clip

    float sign(float x) noexcept;

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
};
