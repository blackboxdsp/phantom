/*
  ==============================================================================

    PhantomLFO.h
    Created: 27 Jan 2021 18:51:41
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "JuceHeader.h"

/**
 * The audio component for applying low-frequency modulations to
 * other areas in the synthesizer, namely filters, oscillators, phasors, 
 * etc.
 */
class PhantomLFO : public HighResolutionTimer
{
public:
    PhantomLFO(AudioProcessorValueTreeState&, int);
    ~PhantomLFO();

    /**
     * Called when the high-resolution timer hits zero.
     */
    void hiResTimerCallback() override;

    /**
     * Updates the LFO's parameters, namely rate and shape.
     * @param sampleRate The sample rate needed for calculating the phase delta, determining read speed.
     */
    void update(float sampleRate) noexcept;

    /**
     * Computes the next value for the LFO. 
     * CAUTION: The output of this function is in biopolar format, meaning that 
     * it is in the range [-1.0f, 1.0f).
     * @returns The next value read from the LFO.
     */
    float evaluate() noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomLFO)

    /**
     * Initializes the parameters for the LFO.
     */
    void initParameters();

    /**
     * Resets the wavetable according the current shape parameter.
     */
    void resetWavetable() noexcept;

    /**
     * Updates the phase delta, which determines the read speed (affecting
     * the rate).
     */
    void updatePhaseDelta() noexcept;

    /**
     * The wavetable, which is an array of float values.
     */
    Array<float> m_wavetable;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for the LFO's rate.
     */
    std::atomic<float>* p_rate;

    /**
     * The atomic parameter pointer for the LFO's shape.
     */
    std::atomic<float>* p_shape;

    /**
     * The LFO identifier, useful in assigning the correct 
     * `AudioProcessorValueTreeState` paramteres.
     */
    int m_lfoNumber;

    /**
     * The previous shape value, which helps to reduce the
     * amount of times the wavetable is updated (aka rewritten).
     */
    float m_previousShape;

    /**
     * The phase indicating the current position to read in
     * computing the next wave value.
     */
    float m_phase = 0.0f;

    /**
     * The amount to increase the phase by after every wavetable
     * read, which ultimately determines the wave's frequency.
     */
    float m_phaseDelta = 0.0f;

    /**
     * The sample rate, useful in computing the correct phase delta 
     * value for a given frequency.
     */
    float m_sampleRate;

    /**
     * The last read sample value.
     */
    float m_sampleValue = 0.0f;
};
