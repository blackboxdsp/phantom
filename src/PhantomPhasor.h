/*
  ==============================================================================

    PhantomPhasor.h
    Created: 27 Jan 2021 13:03:12
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomPhasor
{
public:
    //==========================================================================
    PhantomPhasor(AudioProcessorValueTreeState&);
    ~PhantomPhasor();

    //==========================================================================
    float apply(float oldPhase, float egMod, float lfoMod) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomPhasor)

    //==========================================================================
    float evaluate(float oldPhase) noexcept;

    float sawtooth(float phase) noexcept;

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_shape;
    std::atomic<float>* p_egInt;
    std::atomic<float>* p_lfoInt;
};
