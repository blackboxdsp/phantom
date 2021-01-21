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
    void initWavetable();

    //==========================================================================
    void setPhaseDelta(double frequency, double sampleRate);

private:
    //==========================================================================
    Array<float> wavetable;
    int wavetableSize;

    double currentPhase = 0.0;
    double previousPhase = 0.0;
    double phaseDelta = 0.0;
};
