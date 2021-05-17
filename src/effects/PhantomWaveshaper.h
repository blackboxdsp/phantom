/*
  ==============================================================================

    PhantomWaveshaper.h
    Created: 02 Feb 2021 23:02:00
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_WAVESHAPER_EFFECT_H
#define _PHANTOM_WAVESHAPER_EFFECT_H

#include "JuceHeader.h"

/**
 * The audio component for waveshaping real-time signals.
 */
class PhantomWaveshaper
{
public:
    PhantomWaveshaper();
    ~PhantomWaveshaper();
    
    /**
     * NOTE: The following waveshaper functions are (roughly)
     * listed in order of increasing intensity. Each functions returns a 
     * waveshaped value in between the range [-1.0f, 1.0f]. 
     */

    /**
     * Fuzz Exponential 2
     */
    float fexp2(float x) noexcept;

    /**
     * Arctangent Square Root
     */
    float atsr(float x) noexcept;

    /**
     * Cube
     */
    float cube(float x) noexcept;

    /**
     * Hyberbolic Tangent
     */
    float htan(float k, float x) noexcept;

    /**
     * Hard Clip
     */
    float hclip(float x) noexcept;

    /**
     * Clips a value between a lower and upper bound.
     * @param x The value to clip.
     * @param lower The lower bound to use.
     * @param upper The upper bound to use.
     * @returns The clipped value between the lower and upper bounds.
     */
    static float clip(float x, float lower, float upper) noexcept { return std::max(lower, std::min(x, upper)); };


    /**
     * Determines the sign of a value.
     * @param x The value to use in determining polarity.
     * @returns The sign of a value (-1.0f if below zero, else 1.0f).
     */
    static float sign(float x) noexcept { return x >= 0.0f ? 1.0f : -1.0f; };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomWaveshaper)
};

#endif
