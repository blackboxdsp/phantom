/*
  ==============================================================================

    PhantomUtils.h
    Created: 22 Jan 2021 10:22:44
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#ifndef PHANTOM_CONSTS
#define PHANTOM_CONSTS

/**
 * The global constants to use in Phantom, largely used for 
 * `AudioProcessorValueTreeState` parameters.
 */
namespace Consts
{
    // AMP

    constexpr char *_LEVEL_PARAM_ID = (char*) "level";
    constexpr char *_LEVEL_PARAM_NAME = (char*) "Level";
    constexpr float _LEVEL_DEFAULT_VAL = 0.0f;

    // OSCILLATORs

    constexpr char *_OSC_SYNC_PARAM_ID = (char*) "oscSync";
    constexpr char *_OSC_SYNC_PARAM_NAME = (char*) "Osc Sync";
    constexpr float _OSC_SYNC_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_RANGE_PARAM_ID = (char*) "osc01Range";
    constexpr char *_OSC_01_RANGE_PARAM_NAME = (char*) "Osc 1 Range";
    constexpr float _OSC_01_RANGE_DEFAULT_VAL = 2.0f;
    constexpr char *_OSC_01_COARSE_TUNE_PARAM_ID = (char*) "osc01CoarseTune";
    constexpr char *_OSC_01_COARSE_TUNE_PARAM_NAME = (char*) "Osc 1 Coarse Tune";
    constexpr float _OSC_01_COARSE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_FINE_TUNE_PARAM_ID = (char*) "osc01FineTune";
    constexpr char *_OSC_01_FINE_TUNE_PARAM_NAME = (char*) "Osc 1 Fine Tune";
    constexpr float _OSC_01_FINE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_SHAPE_INT_PARAM_ID = (char*) "osc01ShapeInt";
    constexpr char *_OSC_01_SHAPE_INT_PARAM_NAME = (char*) "Osc 1 Shape Int";
    constexpr float _OSC_01_SHAPE_INT_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_MOD_DEPTH_PARAM_ID = (char*) "osc01ModDepth";
    constexpr char *_OSC_01_MOD_DEPTH_PARAM_NAME = (char*) "Osc 1 Mod Depth";
    constexpr float _OSC_01_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_MOD_SOURCE_PARAM_ID = (char*) "osc01ModSource";
    constexpr char *_OSC_01_MOD_SOURCE_PARAM_NAME = (char*) "Osc 1 Mod Source";
    constexpr float _OSC_01_MOD_SOURCE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_RANGE_PARAM_ID = (char*) "osc02Range";
    constexpr char *_OSC_02_RANGE_PARAM_NAME = (char*) "Osc 2 Range";
    constexpr float _OSC_02_RANGE_DEFAULT_VAL = 2.0f;
    constexpr char *_OSC_02_COARSE_TUNE_PARAM_ID = (char*) "osc02CoarseTune";
    constexpr char *_OSC_02_COARSE_TUNE_PARAM_NAME = (char*) "Osc 2 Coarse Tune";
    constexpr float _OSC_02_COARSE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_FINE_TUNE_PARAM_ID = (char*) "osc02FineTune";
    constexpr char *_OSC_02_FINE_TUNE_PARAM_NAME = (char*) "Osc 2 Fine Tune";
    constexpr float _OSC_02_FINE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_SHAPE_INT_PARAM_ID = (char*) "osc02ShapeInt";
    constexpr char *_OSC_02_SHAPE_INT_PARAM_NAME = (char*) "Osc 2 Shape Int";
    constexpr float _OSC_02_SHAPE_INT_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_MOD_DEPTH_PARAM_ID = (char*) "osc02ModDepth";
    constexpr char *_OSC_02_MOD_DEPTH_PARAM_NAME = (char*) "Osc 2 Mod Depth";
    constexpr float _OSC_02_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_MOD_SOURCE_PARAM_ID = (char*) "osc02ModSource";
    constexpr char *_OSC_02_MOD_SOURCE_PARAM_NAME = (char*) "Osc 2 Mod Source";
    constexpr float _OSC_02_MOD_SOURCE_DEFAULT_VAL = 0.0f;

    // PHASORs

    constexpr char *_PHASOR_01_SHAPE_PARAM_ID = (char*) "phasor01Shape";
    constexpr char *_PHASOR_01_SHAPE_PARAM_NAME = (char*) "Phasor 1 Shape";
    constexpr float _PHASOR_01_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char *_PHASOR_01_EG_INT_PARAM_ID = (char*) "phasor01EgInt";
    constexpr char *_PHASOR_01_EG_INT_PARAM_NAME = (char*) "Phasor 1 EG Int";
    constexpr float _PHASOR_01_EG_INT_DEFAULT_VAL = 1.0f;
    constexpr char *_PHASOR_01_LFO_INT_PARAM_ID = (char*) "phasor01LfoInt";
    constexpr char *_PHASOR_01_LFO_INT_PARAM_NAME = (char*) "Phasor 1 LFO Int";
    constexpr float _PHASOR_01_LFO_INT_DEFAULT_VAL = 0.0f;
    constexpr char *_PHASOR_02_SHAPE_PARAM_ID = (char*) "phasor02Shape";
    constexpr char *_PHASOR_02_SHAPE_PARAM_NAME = (char*) "Phasor 2 Shape";
    constexpr float _PHASOR_02_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char *_PHASOR_02_EG_INT_PARAM_ID = (char*) "phasor02EgInt";
    constexpr char *_PHASOR_02_EG_INT_PARAM_NAME = (char*) "Phasor 2 EG Int";
    constexpr float _PHASOR_02_EG_INT_DEFAULT_VAL = 1.0f;
    constexpr char *_PHASOR_02_LFO_INT_PARAM_ID = (char*) "phasor02LfoInt";
    constexpr char *_PHASOR_02_LFO_INT_PARAM_NAME = (char*) "Phasor 2 LFO Int";
    constexpr float _PHASOR_02_LFO_INT_DEFAULT_VAL = 0.0f;

    // MIXER

    constexpr char *_MIXER_OSC_BAL_PARAM_ID = (char*) "mixerOscBalance";
    constexpr char *_MIXER_OSC_BAL_PARAM_NAME = (char*) "Mixer Osc Balance";
    constexpr float _MIXER_OSC_BAL_DEFAULT_VAL = 0.5f;
    constexpr char *_MIXER_RING_MOD_PARAM_ID = (char*) "mixerRngMod";
    constexpr char *_MIXER_RING_MOD_PARAM_NAME = (char*) "Mixer Rng Mod";
    constexpr float _MIXER_RING_MOD_DEFAULT_VAL = 0.0;
    constexpr char *_MIXER_NOISE_PARAM_ID = (char*) "mixerNoise";
    constexpr char *_MIXER_NOISE_PARAM_NAME = (char*) "Mixer Noise";
    constexpr float _MIXER_NOISE_DEFAULT_VAL = 0.0;

    // FILTERs

    constexpr char *_FLTR_CUTOFF_PARAM_ID = (char*) "filterCutoff";
    constexpr char *_FLTR_CUTOFF_PARAM_NAME = (char*) "Filter Cutoff";
    constexpr float _FLTR_CUTOFF_DEFAULT_VAL = 1000.0f;
    constexpr char *_FLTR_RESO_PARAM_ID = (char*) "filterReso";
    constexpr char *_FLTR_RESO_PARAM_NAME = (char*) "Filter Resonance";
    constexpr float _FLTR_RESO_DEFAULT_VAL = 0.70710678;
    constexpr char *_FLTR_DRIVE_PARAM_ID = (char*) "filterDrive";
    constexpr char *_FLTR_DRIVE_PARAM_NAME = (char*) "Filter Drive";
    constexpr float _FLTR_DRIVE_DEFAULT_VAL = 0.0f;
    constexpr char *_FLTR_EG_MOD_DEPTH_PARAM_ID = (char*) "filterEgModDepth";
    constexpr char *_FLTR_EG_MOD_DEPTH_PARAM_NAME = (char*) "Filter EG Mod Depth";
    constexpr float _FLTR_EG_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char *_FLTR_LFO_MOD_DEPTH_PARAM_ID = (char*) "filterLfoModDepth";
    constexpr char *_FLTR_LFO_MOD_DEPTH_PARAM_NAME = (char*) "Filter LFO Mod Depth";
    constexpr float _FLTR_LFO_MOD_DEPTH_DEFAULT_VAL = 0.0f;

    // LFOs

    constexpr char *_LFO_01_RATE_PARAM_ID = (char*) "lfo01Rate";
    constexpr char *_LFO_01_RATE_PARAM_NAME = (char*) "LFO 1 Rate";
    constexpr float _LFO_01_RATE_DEFAULT_VAL = 20.0f;
    constexpr char *_LFO_01_SHAPE_PARAM_ID = (char*) "lfo01Shape";
    constexpr char *_LFO_01_SHAPE_PARAM_NAME = (char*) "LFO 1 Shape";
    constexpr float _LFO_01_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char *_LFO_02_RATE_PARAM_ID = (char*) "lfo02Rate";
    constexpr char *_LFO_02_RATE_PARAM_NAME = (char*) "LFO 2 Rate";
    constexpr float _LFO_02_RATE_DEFAULT_VAL = 20.0f;
    constexpr char *_LFO_02_SHAPE_PARAM_ID = (char*) "lfo02Shape";
    constexpr char *_LFO_02_SHAPE_PARAM_NAME = (char*) "LFO 2 Shape";
    constexpr float _LFO_02_SHAPE_DEFAULT_VAL = 0.0f;

    // EGs

    constexpr char *_AMP_EG_ATK_PARAM_ID = (char*) "ampEgAtk";
    constexpr char *_AMP_EG_ATK_PARAM_NAME = (char*) "Amp EG Atk";
    constexpr float _AMP_EG_ATK_DEFAULT_VAL = 0.02f;
    constexpr char *_AMP_EG_DEC_PARAM_ID = (char*) "ampEgDec";
    constexpr char *_AMP_EG_DEC_PARAM_NAME = (char*) "Amp EG Dec";
    constexpr float _AMP_EG_DEC_DEFAULT_VAL = 0.2f;
    constexpr char *_AMP_EG_SUS_PARAM_ID = (char*) "ampEgSus";
    constexpr char *_AMP_EG_SUS_PARAM_NAME = (char*) "Amp EG Sus";
    constexpr float _AMP_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char *_AMP_EG_REL_PARAM_ID = (char*) "ampEgRel";
    constexpr char *_AMP_EG_REL_PARAM_NAME = (char*) "Amp EG Rel";
    constexpr float _AMP_EG_REL_DEFAULT_VAL = 0.6f;

    constexpr char *_FLTR_EG_ATK_PARAM_ID = (char*) "fltrEgAtk";
    constexpr char *_FLTR_EG_ATK_PARAM_NAME = (char*) "Filter EG Atk";
    constexpr float _FLTR_EG_ATK_DEFAULT_VAL = 0.01f;
    constexpr char *_FLTR_EG_DEC_PARAM_ID = (char*) "fltrEgDec";
    constexpr char *_FLTR_EG_DEC_PARAM_NAME = (char*) "Filter EG Dec";
    constexpr float _FLTR_EG_DEC_DEFAULT_VAL = 0.4f;
    constexpr char *_FLTR_EG_SUS_PARAM_ID = (char*) "fltrEgSus";
    constexpr char *_FLTR_EG_SUS_PARAM_NAME = (char*) "Filter EG Sus";
    constexpr float _FLTR_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char *_FLTR_EG_REL_PARAM_ID = (char*) "fltrEgRel";
    constexpr char *_FLTR_EG_REL_PARAM_NAME = (char*) "Filter EG Rel";
    constexpr float _FLTR_EG_REL_DEFAULT_VAL = 0.8f;

    constexpr char *_PHASOR_EG_ATK_PARAM_ID = (char*) "phaseEgAtk";
    constexpr char *_PHASOR_EG_ATK_PARAM_NAME = (char*) "Phase EG Atk";
    constexpr float _PHASOR_EG_ATK_DEFAULT_VAL = 0.1f;
    constexpr char *_PHASOR_EG_DEC_PARAM_ID = (char*) "phaseEgDec";
    constexpr char *_PHASOR_EG_DEC_PARAM_NAME = (char*) "Phase EG Dec";
    constexpr float _PHASOR_EG_DEC_DEFAULT_VAL = 0.25f;
    constexpr char *_PHASOR_EG_SUS_PARAM_ID = (char*) "phaseEgSus";
    constexpr char *_PHASOR_EG_SUS_PARAM_NAME = (char*) "Phase EG Sus";
    constexpr float _PHASOR_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char *_PHASOR_EG_REL_PARAM_ID = (char*) "phaseEgRel";
    constexpr char *_PHASOR_EG_REL_PARAM_NAME = (char*) "Phase EG Rel";
    constexpr float _PHASOR_EG_REL_DEFAULT_VAL = 1.2f;

    constexpr char *_MOD_EG_ATK_PARAM_ID = (char*) "modEgAtk";
    constexpr char *_MOD_EG_ATK_PARAM_NAME = (char*) "Mod EG Atk";
    constexpr float _MOD_EG_ATK_DEFAULT_VAL = 0.01f;
    constexpr char *_MOD_EG_DEC_PARAM_ID = (char*) "modEgDec";
    constexpr char *_MOD_EG_DEC_PARAM_NAME = (char*) "Mod EG Dec";
    constexpr float _MOD_EG_DEC_DEFAULT_VAL = 0.15f;
    constexpr char *_MOD_EG_SUS_PARAM_ID = (char*) "modEgSus";
    constexpr char *_MOD_EG_SUS_PARAM_NAME = (char*) "Mod EG Sus";
    constexpr float _MOD_EG_SUS_DEFAULT_VAL = -60.0f;
    constexpr char *_MOD_EG_REL_PARAM_ID = (char*) "modEgRel";
    constexpr char *_MOD_EG_REL_PARAM_NAME = (char*) "Mod EG Rel";
    constexpr float _MOD_EG_REL_DEFAULT_VAL = 0.2f;

    constexpr int _WAVETABLE_SIZE = 1 << 11;

    const Colour _STROKE_COLOUR = Colour::fromRGBA(100, 222, 250, 205);
    const Colour _FILL_START_COLOUR = Colour::fromRGBA(77, 202, 227, 205);
    const Colour _FILL_END_COLOUR = Colour::fromRGBA(42, 178, 209, 205);
}

#endif

#ifndef EG_TYPE_ENUM
#define EG_TYPE_ENUM

/**
 * The enum specifying different envelope generator types.
 */
enum EnvelopeGeneratorType
{
    AMP = 0,
    FLTR = 1,
    PHASE = 2,
    MOD = 3
};

#endif
