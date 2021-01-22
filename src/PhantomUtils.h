/*
  ==============================================================================

    PhantomUtils.h
    Created: 22 Jan 2021 10:22:44am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==========================================================================
namespace Parameters {
    constexpr char* _OSC_RANGE_PARAM_ID = "oscRange";
    constexpr char* _OSC_RANGE_PARAM_NAME = "Osc Range";
    constexpr float _OSC_RANGE_DEFAULT_VAL = 2.0f;
    constexpr char* _OSC_TUNE_PARAM_ID = "oscTune";
    constexpr char* _OSC_TUNE_PARAM_NAME = "Osc Tune";
    constexpr float _OSC_TUNE_DEFAULT_VAL = 0.0f;

    constexpr char* _AMP_EG_ATK_PARAM_ID = "ampEgAtk";
    constexpr char* _AMP_EG_ATK_PARAM_NAME = "Amp EG Atk";
    constexpr float _AMP_EG_ATK_DEFAULT_VAL = 0.1f;
    constexpr char* _AMP_EG_DEC_PARAM_ID = "ampEgDec";
    constexpr char* _AMP_EG_DEC_PARAM_NAME = "Amp EG Dec";
    constexpr float _AMP_EG_DEC_DEFAULT_VAL = 0.25f;
    constexpr char* _AMP_EG_SUS_PARAM_ID = "ampEgSus";
    constexpr char* _AMP_EG_SUS_PARAM_NAME = "Amp EG Sus";
    constexpr float _AMP_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char* _AMP_EG_REL_PARAM_ID = "ampEgRel";
    constexpr char* _AMP_EG_REL_PARAM_NAME = "Amp EG Rel";
    constexpr float _AMP_EG_REL_DEFAULT_VAL = 1.2f;

    constexpr char* _LEVEL_PARAM_ID = "level";
    constexpr char* _LEVEL_PARAM_NAME = "Level";
    constexpr float _LEVEL_DEFAULT_VAL = 0.0f;
}
