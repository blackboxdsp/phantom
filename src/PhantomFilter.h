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
#include "PhantomWaveshaper.h"

/**
 * The audio component for filtering real-time audio signals.
 */
class PhantomFilter
{
public:
    PhantomFilter(AudioProcessorValueTreeState&, dsp::ProcessSpec&);
    ~PhantomFilter();

    /**
     * Updates the parameters for the filter like resonance, drive, EG/LFO 
     * mod intensity, etc.).
     */
    void update() noexcept;

    /**
     * Filters a sample value.
     * @param sample The original sample value to filter.
     * @param egMod The intensity of the envelope generator modulation.
     * @param lfoMod The intensity of the LFO modulation.
     * @returns The filtered sample value with resonance, drive, and modulations applied.
     */
    float evaluate(float sample, float egMod, float lfoMod) noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomFilter)

    /**
     * The unique pointer for the JUCE filter used in Phantom's implementation.
     */
    std::unique_ptr<dsp::StateVariableTPTFilter<float>> m_filter;

    /**
     * The unique pointer for the waveshaper, useful in driving a filtered signal.
     */
    std::unique_ptr<PhantomWaveshaper> m_waveshaper;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for the filter's cutoff.
     */
    std::atomic<float>* p_cutoff;

    /**
     * The atomic parameter pointer for the filter's resonance.
     */
    std::atomic<float>* p_resonance;

    /**
     * The atomic parameter pointer for the filter's drive.
     */
    std::atomic<float>* p_drive;

    /**
     * The atomic parameter pointer for the filter's type (low-pass, band-bass,
     * or high-pass).
     */
    std::atomic<float>* p_type;

    /**
     * The atomic parameter pointer for the filter's envelope
     * generator's modulation depth.
     */
    std::atomic<float>* p_egModDepth;

    /**
     * The atomic parameter pointer for the filter's LFO's
     * modulation depth.
     */
    std::atomic<float>* p_lfoModDepth;

    /**
     * The previous frequency value for preventing artifacting
     * when changing and/or automating frequency cutoff.
     */
    float m_previousFrequency = 0.0f;

    /**
     * The number of channels to filter.
     */
    const int k_channelNumber = 0;

    /**
     * The cutoff modulation maximum amount, used as a multiplier.
     */
    const float k_cutoffModulationMultiplier = 3000.0f;

    /**
     * The lower bounds of the filter's cutoff.
     */
    const float k_cutoffLowerBounds = 0.0f;

    /**
     * The upper bounds of the filter's cutoff.
     */
    const float k_cutoffUpperCounds = 11000.0f;
};
