/*
  ==============================================================================

    PhantomEnvelopeGenerator.cpp
    Created: 22 Jan 2021 10:41:40am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomEnvelopeGenerator.h"

//==========================================================================
PhantomEnvelopeGenerator::PhantomEnvelopeGenerator(AudioProcessorValueTreeState& vts, char* parameterIds[4], double sampleRate)
    :   m_parameters(vts)
{
    setSampleRate(sampleRate);

    p_attack = m_parameters.getRawParameterValue(parameterIds[0]);
    p_decay = m_parameters.getRawParameterValue(parameterIds[1]);
    p_sustain = m_parameters.getRawParameterValue(parameterIds[2]);
    p_release = m_parameters.getRawParameterValue(parameterIds[3]);

    update();
}

PhantomEnvelopeGenerator::~PhantomEnvelopeGenerator()
{
    p_attack = nullptr;
    p_decay = nullptr;
    p_sustain = nullptr;
    p_release = nullptr;
}

//==============================================================================
forcedinline void PhantomEnvelopeGenerator::update() noexcept
{
    setEnvelope();
    setParameters(m_envelope);
}

forcedinline void PhantomEnvelopeGenerator::setEnvelope() noexcept
{
    m_envelope.attack = *p_attack;
    m_envelope.decay = *p_decay;
    m_envelope.sustain = powf(2, *p_sustain / 6);
    m_envelope.release = *p_release;
}
