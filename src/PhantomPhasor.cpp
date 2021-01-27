/*
  ==============================================================================

    PhantomPhasor.cpp
    Created: 27 Jan 2021 13:03:12
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomPhasor.h"

#include "PhantomUtils.h"

PhantomPhasor::PhantomPhasor(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    p_shape = m_parameters.getRawParameterValue(Consts::_PHASOR_SHAPE_PARAM_ID);
    p_egModDepth = m_parameters.getRawParameterValue(Consts::_PHASOR_EG_MOD_DEPTH_PARAM_ID);
    p_lfoModDepth = m_parameters.getRawParameterValue(Consts::_PHASOR_LFO_MOD_DEPTH_PARAM_ID);
}

PhantomPhasor::~PhantomPhasor()
{
    p_shape = nullptr;
    p_egModDepth = nullptr;
    p_lfoModDepth = nullptr;
}

//==========================================================================
float PhantomPhasor::apply(float oldPhase) noexcept
{
    oldPhase /= (float) Consts::_WAVETABLE_SIZE;

    float phase = evaluate(oldPhase);

    return phase * (float) Consts::_WAVETABLE_SIZE;
}

float PhantomPhasor::evaluate(float phase) noexcept
{
    float value;

    switch((int) *p_shape)
    {
        default:
        case 0:
            value = sawtooth(phase);
            break;
    }

    return value;
}

//==============================================================================
float PhantomPhasor::sawtooth(float phase) noexcept
{
    if(phase <= 0.05f)
        return 10.0f * phase;
    else
        return 0.52631579f * phase + 0.47368421f;
}
