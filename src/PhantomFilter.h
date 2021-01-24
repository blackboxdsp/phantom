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
    PhantomFilter(AudioProcessorValueTreeState&);
    ~PhantomFilter();

    //==========================================================================
    void PhantomFilter::initFilter();

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomFilter)

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    //==========================================================================
    dsp::LadderFilter<float>* m_filter;
};
