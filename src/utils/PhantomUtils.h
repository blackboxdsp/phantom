/*
  ==============================================================================

    PhantomUtils.h
    Created: 22 Jan 2021 10:22:44
    Author:  Matthew Maxwell

  ==============================================================================
*/


#ifndef PHANTOM_UTILS_H
#define PHANTOM_UTILS_H

#include "JuceHeader.h"

/**
 * The global constants to use in Phantom, largely used for 
 * `AudioProcessorValueTreeState` parameters.
 */
namespace Consts
{
    // AMP

    constexpr char *_LEVEL_PARAM_ID = "level";
    constexpr char *_LEVEL_PARAM_NAME = "Level";
    constexpr float _LEVEL_DEFAULT_VAL = 0.0f;

    // OSCILLATORs

    constexpr char *_OSC_SYNC_PARAM_ID = "oscSync";
    constexpr char *_OSC_SYNC_PARAM_NAME = "Osc Sync";
    constexpr float _OSC_SYNC_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_RANGE_PARAM_ID = "osc01Range";
    constexpr char *_OSC_01_RANGE_PARAM_NAME = "Osc 1 Range";
    constexpr float _OSC_01_RANGE_DEFAULT_VAL = 2.0f;
    constexpr char *_OSC_01_COARSE_TUNE_PARAM_ID = "osc01CoarseTune";
    constexpr char *_OSC_01_COARSE_TUNE_PARAM_NAME = "Osc 1 Coarse Tune";
    constexpr float _OSC_01_COARSE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_FINE_TUNE_PARAM_ID = "osc01FineTune";
    constexpr char *_OSC_01_FINE_TUNE_PARAM_NAME = "Osc 1 Fine Tune";
    constexpr float _OSC_01_FINE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_SHAPE_INT_PARAM_ID = "osc01ShapeInt";
    constexpr char *_OSC_01_SHAPE_INT_PARAM_NAME = "Osc 1 Shape Int";
    constexpr float _OSC_01_SHAPE_INT_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_MOD_DEPTH_PARAM_ID = "osc01ModDepth";
    constexpr char *_OSC_01_MOD_DEPTH_PARAM_NAME = "Osc 1 Mod Depth";
    constexpr float _OSC_01_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_01_MOD_SOURCE_PARAM_ID = "osc01ModSource";
    constexpr char *_OSC_01_MOD_SOURCE_PARAM_NAME = "Osc 1 Mod Source";
    constexpr float _OSC_01_MOD_SOURCE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_RANGE_PARAM_ID = "osc02Range";
    constexpr char *_OSC_02_RANGE_PARAM_NAME = "Osc 2 Range";
    constexpr float _OSC_02_RANGE_DEFAULT_VAL = 2.0f;
    constexpr char *_OSC_02_COARSE_TUNE_PARAM_ID = "osc02CoarseTune";
    constexpr char *_OSC_02_COARSE_TUNE_PARAM_NAME = "Osc 2 Coarse Tune";
    constexpr float _OSC_02_COARSE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_FINE_TUNE_PARAM_ID = "osc02FineTune";
    constexpr char *_OSC_02_FINE_TUNE_PARAM_NAME = "Osc 2 Fine Tune";
    constexpr float _OSC_02_FINE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_SHAPE_INT_PARAM_ID = "osc02ShapeInt";
    constexpr char *_OSC_02_SHAPE_INT_PARAM_NAME = "Osc 2 Shape Int";
    constexpr float _OSC_02_SHAPE_INT_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_MOD_DEPTH_PARAM_ID = "osc02ModDepth";
    constexpr char *_OSC_02_MOD_DEPTH_PARAM_NAME = "Osc 2 Mod Depth";
    constexpr float _OSC_02_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char *_OSC_02_MOD_SOURCE_PARAM_ID = "osc02ModSource";
    constexpr char *_OSC_02_MOD_SOURCE_PARAM_NAME = "Osc 2 Mod Source";
    constexpr float _OSC_02_MOD_SOURCE_DEFAULT_VAL = 0.0f;

    // PHASORs

    constexpr char *_PHASOR_01_SHAPE_PARAM_ID = "phasor01Shape";
    constexpr char *_PHASOR_01_SHAPE_PARAM_NAME = "Phasor 1 Shape";
    constexpr float _PHASOR_01_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char *_PHASOR_01_EG_INT_PARAM_ID = "phasor01EgInt";
    constexpr char *_PHASOR_01_EG_INT_PARAM_NAME = "Phasor 1 EG Int";
    constexpr float _PHASOR_01_EG_INT_DEFAULT_VAL = 1.0f;
    constexpr char *_PHASOR_01_LFO_INT_PARAM_ID = "phasor01LfoInt";
    constexpr char *_PHASOR_01_LFO_INT_PARAM_NAME = "Phasor 1 LFO Int";
    constexpr float _PHASOR_01_LFO_INT_DEFAULT_VAL = 0.0f;
    constexpr char *_PHASOR_02_SHAPE_PARAM_ID = "phasor02Shape";
    constexpr char *_PHASOR_02_SHAPE_PARAM_NAME = "Phasor 2 Shape";
    constexpr float _PHASOR_02_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char *_PHASOR_02_EG_INT_PARAM_ID = "phasor02EgInt";
    constexpr char *_PHASOR_02_EG_INT_PARAM_NAME = "Phasor 2 EG Int";
    constexpr float _PHASOR_02_EG_INT_DEFAULT_VAL = 1.0f;
    constexpr char *_PHASOR_02_LFO_INT_PARAM_ID = "phasor02LfoInt";
    constexpr char *_PHASOR_02_LFO_INT_PARAM_NAME = "Phasor 2 LFO Int";
    constexpr float _PHASOR_02_LFO_INT_DEFAULT_VAL = 0.0f;

    // MIXER

    constexpr char *_MIXER_OSC_BAL_PARAM_ID = "mixerOscBalance";
    constexpr char *_MIXER_OSC_BAL_PARAM_NAME = "Mixer Osc Balance";
    constexpr float _MIXER_OSC_BAL_DEFAULT_VAL = 0.5f;
    constexpr char *_MIXER_AMP_GAIN_PARAM_ID = "mixerAmpGain";
    constexpr char *_MIXER_AMP_GAIN_PARAM_NAME = "Mixer Amp Gain";
    constexpr float _MIXER_AMP_GAIN_DEFAULT_VAL = 1.0f;
    constexpr char *_MIXER_RING_MOD_PARAM_ID = "mixerRingMod";
    constexpr char *_MIXER_RING_MOD_PARAM_NAME = "Mixer Ring Mod";
    constexpr float _MIXER_RING_MOD_DEFAULT_VAL = 0.0;
    constexpr char *_MIXER_NOISE_PARAM_ID = "mixerNoise";
    constexpr char *_MIXER_NOISE_PARAM_NAME = "Mixer Noise";
    constexpr float _MIXER_NOISE_DEFAULT_VAL = 0.0;

    // FILTERs

    constexpr char *_FLTR_CUTOFF_PARAM_ID = "filterCutoff";
    constexpr char *_FLTR_CUTOFF_PARAM_NAME = "Filter Cutoff";
    constexpr float _FLTR_CUTOFF_DEFAULT_VAL = 1000.0f;
    constexpr char *_FLTR_RESO_PARAM_ID = "filterReso";
    constexpr char *_FLTR_RESO_PARAM_NAME = "Filter Resonance";
    constexpr float _FLTR_RESO_DEFAULT_VAL = 0.70710678;
    constexpr char *_FLTR_DRIVE_PARAM_ID = "filterDrive";
    constexpr char *_FLTR_DRIVE_PARAM_NAME = "Filter Drive";
    constexpr float _FLTR_DRIVE_DEFAULT_VAL = 0.0f;
    constexpr char *_FLTR_MODE_PARAM_ID = "filterMode";
    constexpr char *_FLTR_MODE_PARAM_NAME = "Filter Mode";
    constexpr float _FLTR_MODE_DEFAULT_VAL = 0.0f;
    constexpr char *_FLTR_EG_MOD_DEPTH_PARAM_ID = "filterEgModDepth";
    constexpr char *_FLTR_EG_MOD_DEPTH_PARAM_NAME = "Filter EG Mod Depth";
    constexpr float _FLTR_EG_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char *_FLTR_LFO_MOD_DEPTH_PARAM_ID = "filterLfoModDepth";
    constexpr char *_FLTR_LFO_MOD_DEPTH_PARAM_NAME = "Filter LFO Mod Depth";
    constexpr float _FLTR_LFO_MOD_DEPTH_DEFAULT_VAL = 0.0f;

    // LFOs

    constexpr char *_LFO_01_RATE_PARAM_ID = "lfo01Rate";
    constexpr char *_LFO_01_RATE_PARAM_NAME = "LFO 1 Rate";
    constexpr float _LFO_01_RATE_DEFAULT_VAL = 20.0f;
    constexpr char *_LFO_01_SHAPE_PARAM_ID = "lfo01Shape";
    constexpr char *_LFO_01_SHAPE_PARAM_NAME = "LFO 1 Shape";
    constexpr float _LFO_01_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char *_LFO_02_RATE_PARAM_ID = "lfo02Rate";
    constexpr char *_LFO_02_RATE_PARAM_NAME = "LFO 2 Rate";
    constexpr float _LFO_02_RATE_DEFAULT_VAL = 20.0f;
    constexpr char *_LFO_02_SHAPE_PARAM_ID = "lfo02Shape";
    constexpr char *_LFO_02_SHAPE_PARAM_NAME = "LFO 2 Shape";
    constexpr float _LFO_02_SHAPE_DEFAULT_VAL = 0.0f;

    // EGs

    constexpr char *_AMP_EG_ATK_PARAM_ID = "ampEgAtk";
    constexpr char *_AMP_EG_ATK_PARAM_NAME = "Amp EG Attack";
    constexpr float _AMP_EG_ATK_DEFAULT_VAL = 0.02f;
    constexpr char *_AMP_EG_DEC_PARAM_ID = "ampEgDec";
    constexpr char *_AMP_EG_DEC_PARAM_NAME = "Amp EG Decay";
    constexpr float _AMP_EG_DEC_DEFAULT_VAL = 0.2f;
    constexpr char *_AMP_EG_SUS_PARAM_ID = "ampEgSus";
    constexpr char *_AMP_EG_SUS_PARAM_NAME = "Amp EG Sustain";
    constexpr float _AMP_EG_SUS_DEFAULT_VAL = -15.0f;
    constexpr char *_AMP_EG_REL_PARAM_ID = "ampEgRel";
    constexpr char *_AMP_EG_REL_PARAM_NAME = "Amp EG Release";
    constexpr float _AMP_EG_REL_DEFAULT_VAL = 0.6f;

    constexpr char *_PHASOR_EG_ATK_PARAM_ID = "phaseEgAtk";
    constexpr char *_PHASOR_EG_ATK_PARAM_NAME = "Phase EG Attack";
    constexpr float _PHASOR_EG_ATK_DEFAULT_VAL = 0.1f;
    constexpr char *_PHASOR_EG_DEC_PARAM_ID = "phaseEgDec";
    constexpr char *_PHASOR_EG_DEC_PARAM_NAME = "Phase EG Decay";
    constexpr float _PHASOR_EG_DEC_DEFAULT_VAL = 0.25f;
    constexpr char *_PHASOR_EG_SUS_PARAM_ID = "phaseEgSus";
    constexpr char *_PHASOR_EG_SUS_PARAM_NAME = "Phase EG Sustain";
    constexpr float _PHASOR_EG_SUS_DEFAULT_VAL = -15.0f;
    constexpr char *_PHASOR_EG_REL_PARAM_ID = "phaseEgRel";
    constexpr char *_PHASOR_EG_REL_PARAM_NAME = "Phase EG Release";
    constexpr float _PHASOR_EG_REL_DEFAULT_VAL = 1.2f;

    constexpr char *_FLTR_EG_ATK_PARAM_ID = "fltrEgAtk";
    constexpr char *_FLTR_EG_ATK_PARAM_NAME = "Filter EG Attack";
    constexpr float _FLTR_EG_ATK_DEFAULT_VAL = 0.01f;
    constexpr char *_FLTR_EG_DEC_PARAM_ID = "fltrEgDec";
    constexpr char *_FLTR_EG_DEC_PARAM_NAME = "Filter EG Decay";
    constexpr float _FLTR_EG_DEC_DEFAULT_VAL = 0.4f;
    constexpr char *_FLTR_EG_SUS_PARAM_ID = "fltrEgSus";
    constexpr char *_FLTR_EG_SUS_PARAM_NAME = "Filter EG Sustain";
    constexpr float _FLTR_EG_SUS_DEFAULT_VAL = -15.0f;
    constexpr char *_FLTR_EG_REL_PARAM_ID = "fltrEgRel";
    constexpr char *_FLTR_EG_REL_PARAM_NAME = "Filter EG Release";
    constexpr float _FLTR_EG_REL_DEFAULT_VAL = 0.8f;

    constexpr char *_MOD_EG_ATK_PARAM_ID = "modEgAtk";
    constexpr char *_MOD_EG_ATK_PARAM_NAME = "Mod EG Attack";
    constexpr float _MOD_EG_ATK_DEFAULT_VAL = 0.01f;
    constexpr char *_MOD_EG_DEC_PARAM_ID = "modEgDec";
    constexpr char *_MOD_EG_DEC_PARAM_NAME = "Mod EG Decay";
    constexpr float _MOD_EG_DEC_DEFAULT_VAL = 0.15f;
    constexpr char *_MOD_EG_SUS_PARAM_ID = "modEgSus";
    constexpr char *_MOD_EG_SUS_PARAM_NAME = "Mod EG Sustain";
    constexpr float _MOD_EG_SUS_DEFAULT_VAL = -15.0f;
    constexpr char *_MOD_EG_REL_PARAM_ID = "modEgRel";
    constexpr char *_MOD_EG_REL_PARAM_NAME = "Mod EG Release";
    constexpr float _MOD_EG_REL_DEFAULT_VAL = 0.2f;

    constexpr int _WAVETABLE_SIZE = 1 << 11;

    const Colour _STROKE_COLOUR = Colour::fromRGBA(100, 222, 250, 205);
    const Colour _FILL_START_COLOUR = Colour::fromRGBA(77, 202, 227, 205);
    const Colour _FILL_END_COLOUR = Colour::fromRGBA(42, 178, 209, 205);

    constexpr int _TEXT_BOX_WIDTH = 80;
    constexpr int _TEXT_BOX_HEIGHT = 20;

    constexpr char *_COMPANY_NAME = "Black Box DSP";
    constexpr char *_PLUGIN_NAME = "Phantom";
    constexpr char *_PLUGIN_VERSION = "1.0.0-beta";
}

/**
 * Calculates the skew factor given a start, end, and desired center point.
 * @param start The start value to use.
 * @param end The end value to use.
 * @param center The value to skew to the middle.
 * @returns The calculated skew value to accomodate a non-linear slider.
 */
static float calculateSkewFactor(float start, float end, float center)
{
    return std::log(0.5f) / std::log((center - start) / (end - start));
}

#endif
