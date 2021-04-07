/*
  ==============================================================================

    PhantomEnvelopeGenerator.h
    Created: 22 Jan 2021 10:41:40
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PhantomUtils.h"

/**
 * The audio component for generating envelopes, useful in shaping
 * a real-time signal to specific ADSR parameters.
 */
class PhantomEnvelopeGenerator : public ADSR
{
public:
    PhantomEnvelopeGenerator(AudioProcessorValueTreeState&, EnvelopeGeneratorType);
    ~PhantomEnvelopeGenerator();

    /**
     * Updates the envelope's parameters (ADSR).
     */
    void update() noexcept;

    /**
     * Computes the next value for the envelope.
     * @returns The next generated envelope value.
     */
    float evaluate() noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomEnvelopeGenerator)

    /**
     * Sets the envelope type, relevant for binding to
     * the appropriate `AudioProcessValueTreeState` parameter.
     */
    void setEnvelopeType();

    /**
     * Updates the ADSR parameters with the atomic parameter
     * values.
     */
    void setEnvelopeParameters() noexcept;

    /**
     * The envelope ADSR parameters struct.
     */
    juce::ADSR::Parameters m_envelope;

    /**
     * The envelope generator type (enum value)
     */
    EnvelopeGeneratorType m_type;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter value for the EG' attack.
     */
    std::atomic<float>* p_attack;

    /**
     * The atomic parameter value for the EG' decay.
     */
    std::atomic<float>* p_decay;

    /**
     * The atomic parameter value for the EG' sustain.
     */
    std::atomic<float>* p_sustain;

    /**
     * The atomic parameter value for the EG' release.
     */
    std::atomic<float>* p_release;

    /**
     * The previous sustain value for preventing artifacting
     * on fast sustain changes and/or automation.
     */
    float m_previousSustain;
};
