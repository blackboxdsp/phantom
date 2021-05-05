/*
  ==============================================================================

    PhantomPhasor.h
    Created: 27 Jan 2021 13:03:12
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/**
 * The audio component for applying the phase distortion (intended for a 
 * `PhantomOscillator`) effect.
 */
class PhantomPhasor
{
public:
    PhantomPhasor(AudioProcessorValueTreeState&, int);
    ~PhantomPhasor();

    /**
     * Applies the phase distortion effect to a given phase.
     * @param phase The phase value to apply the effect to.
     * @param egMod The envelope generator modulation value.
     * @param lfoMod The LFO modulation value.
     * @returns The phase-distorted value with modulation applied.
     */
    float apply(float phase, float egMod, float lfoMod) noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomPhasor)

    /**
     * Initializes `AudioProcessorValueTreeState` parameters for the phasor.
     */
    void initParameters();

    /**
     * Computes the phase distortion effect for a given phase value.
     * @param phase The phase value to apply the effect to.
     * @returns The phase-distorted value.
     */
    float evaluate(float phase) noexcept;

    /**
     * Computes the phase distortion values for a sawtooth-like sound.
     * @param phase The phase value to use.
     * @returns The phase-distorted value for a sawtooth.
     */
    float sawtooth(float phase) noexcept;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for the phasor's shape.
     */
    std::atomic<float>* p_shape;

    /**
     * The atomic parameter pointer for the phasor's envelope
     * generator intensity.
     */
    std::atomic<float>* p_egInt;

    /**
     * The atomic parameter pointer for the phasor's LFO intensity.
     */
    std::atomic<float>* p_lfoInt;

    /**
     * The phasor identifier, useful in assigning the correct 
     * `AudioProcessorValueTreeState` parameters.
     */
    int m_phasorNumber;
};
