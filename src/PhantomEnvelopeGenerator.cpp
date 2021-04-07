/*
  ==============================================================================

    PhantomEnvelopeGenerator.cpp
    Created: 22 Jan 2021 10:41:40
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomEnvelopeGenerator.h"

PhantomEnvelopeGenerator::PhantomEnvelopeGenerator(AudioProcessorValueTreeState& vts, EnvelopeGeneratorType type)
    :   m_parameters(vts), m_type(type)
{
    setEnvelopeType();
    setEnvelopeParameters();
}

PhantomEnvelopeGenerator::~PhantomEnvelopeGenerator()
{
    p_attack = nullptr;
    p_decay = nullptr;
    p_sustain = nullptr;
    p_release = nullptr;
}

void PhantomEnvelopeGenerator::update() noexcept
{
    setEnvelopeParameters();
    setParameters(m_envelope);
}

float PhantomEnvelopeGenerator::evaluate() noexcept
{
    return getNextSample();
}

void PhantomEnvelopeGenerator::setEnvelopeType()
{
    jassert((int) m_type != -1);

    char* atkParamId;
    char* decParamId;
    char* susParamId;
    char* relParamId;

    switch(m_type)
    {
        default:
        case AMP:
            atkParamId = Consts::_AMP_EG_ATK_PARAM_ID;
            decParamId = Consts::_AMP_EG_DEC_PARAM_ID;
            susParamId = Consts::_AMP_EG_SUS_PARAM_ID;
            relParamId = Consts::_AMP_EG_REL_PARAM_ID;
            break;

        case FLTR:
            atkParamId = Consts::_FLTR_EG_ATK_PARAM_ID;
            decParamId = Consts::_FLTR_EG_DEC_PARAM_ID;
            susParamId = Consts::_FLTR_EG_SUS_PARAM_ID;
            relParamId = Consts::_FLTR_EG_REL_PARAM_ID;
            break;

        case PHASE:
            atkParamId = Consts::_PHASOR_EG_ATK_PARAM_ID;
            decParamId = Consts::_PHASOR_EG_DEC_PARAM_ID;
            susParamId = Consts::_PHASOR_EG_SUS_PARAM_ID;
            relParamId = Consts::_PHASOR_EG_REL_PARAM_ID;
            break;

        case MOD:
            atkParamId = Consts::_MOD_EG_ATK_PARAM_ID;
            decParamId = Consts::_MOD_EG_DEC_PARAM_ID;
            susParamId = Consts::_MOD_EG_SUS_PARAM_ID;
            relParamId = Consts::_MOD_EG_REL_PARAM_ID;
            break;
    }

    p_attack = m_parameters.getRawParameterValue(atkParamId);
    p_decay = m_parameters.getRawParameterValue(decParamId);
    p_sustain = m_parameters.getRawParameterValue(susParamId);
    p_release = m_parameters.getRawParameterValue(relParamId);
}

void PhantomEnvelopeGenerator::setEnvelopeParameters() noexcept
{
    m_envelope.attack = *p_attack;
    m_envelope.decay = *p_decay;
    m_envelope.release = *p_release;

    float sustain = powf(2, *p_sustain / 6);
    if(m_envelope.sustain != sustain)
        m_envelope.sustain = (m_envelope.sustain + sustain) / 2.0f;
}
