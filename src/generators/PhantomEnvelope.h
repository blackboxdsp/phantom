/*
  ==============================================================================

    PhantomEnvelope.h
    Created: 22 Jan 2021 10:41:40
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_ENVELOPE_GENERATOR_H
#define _PHANTOM_ENVELOPE_GENERATOR_H

#include "JuceHeader.h"

/** The enum specifying different envelope generator types. */
enum EnvelopeType
{
    AMP     = 0,
    FLTR    = 1,
    PHASE   = 2,
    MOD     = 3
};

/**
 * The audio component for generating envelopes, useful in shaping
 * a real-time signal to specific ADSR parameters.
 */
class PhantomEnvelope : public ADSR
{
public:
    PhantomEnvelope(AudioProcessorValueTreeState& vts, EnvelopeType type);
    ~PhantomEnvelope();

    /**
     * Updates the envelope's parameters (ADSR).
     * @param sampleRate The sample rate to use in calculating the envelope.
     */
    void update(float sampleRate) noexcept;

    /**
     * Computes the next value for the envelope.
     * @returns The next generated envelope value.
     */
    float evaluate() noexcept;

    /** The atomic parameter value for the EG' sustain. */
    std::atomic<float>* p_sustain;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomEnvelope)

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

    /** The envelope ADSR parameters struct. */
    ADSR::Parameters m_envelope;

    /** The envelope generator type (enum value). */
    EnvelopeType m_type = (EnvelopeType) -1;

    AudioProcessorValueTreeState& m_parameters;

    /** The atomic parameter value for the EG' attack. */
    std::atomic<float>* p_attack;

    /** The atomic parameter value for the EG' decay. */
    std::atomic<float>* p_decay;

    // /** The atomic parameter value for the EG' sustain. */
    // std::atomic<float>* p_sustain;

    /** The atomic parameter value for the EG' release. */
    std::atomic<float>* p_release;

    /**
     * The previous sustain value for preventing artifacting
     * on fast sustain changes and/or automation.
     * CAUTION: This value is in units of decibels (dB).
     */
    float m_previousSustain;

    /** The previous envelope value to avoid discontinuities. */
    float m_previousSample = 0.0f;
};

#endif
