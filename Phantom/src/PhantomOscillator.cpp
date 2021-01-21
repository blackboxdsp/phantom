/*
  ==============================================================================

    PhantomOscillator.cpp
    Created: 20 Jan 2021 9:17:28pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscillator.h"

//==========================================================================
PhantomOscillator::PhantomOscillator()
{

}

PhantomOscillator::~PhantomOscillator()
{

}

//==============================================================================
void PhantomOscillator::initWavetable()
{
    wavetable.clear();

    for (int i = 0; i < wavetableSize; i++)
    {
        float value = sinf(MathConstants<float>::twoPi * (float) i / wavetableSize);
        wavetable.insert(i, value);
    }
}

//==============================================================================
void PhantomOscillator::setPhaseDelta(double frequency, double sampleRate)
{
    auto cyclesPerSample = frequency / sampleRate;
    phaseDelta = cyclesPerSample * (double) wavetableSize;
}
