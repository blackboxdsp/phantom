/*
  ==============================================================================

    PhantomMixer.h
    Created: 05 Apr 2021 14:11:33
    Author:  Matthew Maxwell

  ==============================================================================
*/

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

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for oscillator balance, which mixes the output between
     * oscillator 1 and 2.
     */
    std::atomic<float>* p_oscBalance;
    
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
     * The unique pointer to a `Random` object, which generates random values for the noise.
     */
    std::unique_ptr<Random> m_rng;
};
