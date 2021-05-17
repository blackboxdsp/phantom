/*
  ==============================================================================

    PhantomAmplifier.h
    Created: 23 Jan 2021 18:23:35
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_AMPLIFIER_EFFECT_H
#define _PHANTOM_AMPLIFIER_EFFECT_H

#include "JuceHeader.h"

/**
 * The audio component that applies a gain (ramped as necessary)
 * to an audio buffer.
 */
class PhantomAmplifier
{
public:
    
    PhantomAmplifier(AudioProcessorValueTreeState&);
    ~PhantomAmplifier();

    /**
     * Applies the amplifier to the buffer whose reference was
     * passed in.
     * @param buffer The `AudioBuffer` to apply the gain multiplier to.
     */
    void apply(AudioBuffer<float>&) noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAmplifier)
    
    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for the amplifier level,
     * which is in units of decibels (dB).
     */
    std::atomic<float>* p_level = nullptr;

    /**
     * The previous gain value, useful for eliminating discontinuities
     * between buffers. 
     * NOTE: The gain is a float between 0.0f and 1.0f, which is different
     * from the level (in decibels).
     */
    float m_previousGain;
};

#endif
