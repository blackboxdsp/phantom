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

//==============================================================================
/**
*/
class PhantomEnvelopeGenerator : public ADSR
{
public:
    //==========================================================================
    PhantomEnvelopeGenerator(AudioProcessorValueTreeState&, EnvelopeGeneratorType);
    ~PhantomEnvelopeGenerator();

    //==========================================================================
    void update();

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomEnvelopeGenerator)

    //==========================================================================
    juce::ADSR::Parameters m_envelope;

    //==========================================================================
    void setEnvelopeType();
    void setEnvelopeParameters();

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_attack;
    std::atomic<float>* p_decay;
    std::atomic<float>* p_sustain;
    std::atomic<float>* p_release;

    float m_previousSustain;

    //==========================================================================
    EnvelopeGeneratorType m_type;
};
