/*
  ==============================================================================

    PhantomMixer.h
    Created: 05 Apr 2021 14:11:33
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_MIXER_EFFECT_H
#define _PHANTOM_MIXER_EFFECT_H

#include "JuceHeader.h"

/**
 * Class for mixing things like oscillator outputs and also applying effects,
 * namely ring modulation and random noise.
 */
class PhantomMixer
{
public:
    PhantomMixer(AudioProcessorValueTreeState&);
    ~PhantomMixer();

    /**
     * Mixes two oscillator values along with optional parameters: ring modulation
     * and noise.
     * @param osc01Val The first oscillator sample value.
     * @param osc02Val The second oscillator sample value.
     * @noexcept
     */
    float evaluate(float osc01Val, float osc02Val) noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomMixer)

    /**
     * The unique pointer to a `Random` object, which generates random values for the noise.
     */
    std::unique_ptr<Random> m_rng;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for oscillator balance, which mixes the output between
     * oscillator 1 and 2.
     */
    std::atomic<float>* p_oscBalance;

    /**
     * The atomic parameter pointer for amplifier gain, which effectively controls
     * how much of the signal is output by the mixer (in terms of amplitude).
     */
    std::atomic<float>* p_ampGain;
    
    /**
     * The atomic parameter pointer for ring modulation, which controls the level that ring
     * modulation will be added to the output.
     */
    std::atomic<float>* p_ringMod;
    
    /**
     * The atomic parameter pointer for random noise, which controls the level that noise 
     * will be added to the output.
     */
    std::atomic<float>* p_noise;

    /**
     * The previous value for the noise, to help discontinuities.
     */
    float m_previousNoise;
};

#endif
