/*
  ==============================================================================

    PhantomOscillator.h
    Created: 20 Jan 2021 9:17:28pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomOscillator 
{
public:
    //==========================================================================
    PhantomOscillator();
    ~PhantomOscillator();
    
    //==========================================================================
    void initWavetable();

    //==========================================================================
    void setPhaseDelta(double frequency, double sampleRate);

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscillator)

    //==========================================================================
    Array<float> wavetable;
    int wavetableSize = 1 << 10;

    double currentPhase = 0.0;
    double previousPhase = 0.0;
    double phaseDelta = 0.0;
};
