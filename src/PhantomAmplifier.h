/*
  ==============================================================================

    PhantomAmplifier.h
    Created: 23 Jan 2021 18:23:35
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomAmplifier
{
public:
    //==========================================================================
    PhantomAmplifier(AudioProcessorValueTreeState&);
    ~PhantomAmplifier();

    //==========================================================================
    void apply(AudioBuffer<float>&) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAmplifier)
    
    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_level = nullptr;
    float m_previousGain;
};
