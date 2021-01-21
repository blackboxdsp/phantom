/*
  ==============================================================================

    PhantomOscillator.cpp
    Created: 20 Jan 2021 9:17:28pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscillator.h"

//==============================================================================
void PhantomOscillator::initWavetable()
{
    wavetable.clear();

    for (int i = 0; i < wavetableSize; i++)
        {
            float val = sinf(MathConstants<float>::twoPi * (float) i / wavetableSize);
            wavetable.insert(i, val);
        }
}

//==============================================================================
void PhantomOscillator::setPhaseDelta(double frequency, double sampleRate)
{
    auto cyclesPerSample = frequency / sampleRate;
    phaseDelta = cyclesPerSample * (double) wavetableSize;
}
