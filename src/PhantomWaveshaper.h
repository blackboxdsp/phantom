/*
  ==============================================================================

    PhantomWaveshaper.h
    Created: 02 Feb 2021 23:02:00
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomWaveshaper
{
public:
    //==========================================================================
    PhantomWaveshaper();
    ~PhantomWaveshaper();

    //==========================================================================
    
    /* Fuzz Exponential 2 */
    float fexp2(float x) noexcept;
    /* Arctangent Square Root */
    float atsr(float x) noexcept;
    /* Cube */
    float cube(float x) noexcept;
    /* Hyberbolic Tangent */
    float htan(float k, float x) noexcept;
    /* Hard Clip */
    float hclip(float x) noexcept;

    //==========================================================================
    
    /* Return value restricted to range from lower to upper */
    float clip(float x, float lower, float upper) noexcept;
    /* Returns the sign of a value (-1.0f, +1.0f) */
    float sign(float x) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomWaveshaper)
};
