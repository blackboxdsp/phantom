/*
  ==============================================================================

    PhantomEnvelopeGenerator.h
    Created: 22 Jan 2021 10:41:40am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomEnvelopeGenerator : public ADSR
{
public:
    //==========================================================================
    PhantomEnvelopeGenerator(AudioProcessorValueTreeState&, char* [4]);
    ~PhantomEnvelopeGenerator();

    //==========================================================================
    void init();

    //==========================================================================
    void update();

private:
    //==========================================================================
    ADSR::Parameters m_envelope;

    //==========================================================================
    void setEnvelope();

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_attack;
    std::atomic<float>* p_decay;
    std::atomic<float>* p_sustain;
    std::atomic<float>* p_release;
};
