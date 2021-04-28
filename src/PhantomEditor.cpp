/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"
#include "PhantomProcessor.h"
#include "PhantomUtils.h"

PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), m_processor(p), m_parameters(vts)
{
    initLayoutVariables();

    initAmpGui();
    initOscillatorGui();
    initPhasorGui();
    initMixerGui();
    initFilterGui();
    initLfoGui();
    initEgGui();

    initAnalyzer();
    initOscilloscope();

    initPresetMenu();

    setResizable(true, true);
    setSize(1280, 720);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    m_oscilloscope = nullptr;
    m_analyzer = nullptr;

    m_levelSliderAttachment = nullptr;

    m_oscSyncSliderAttachment = nullptr;
    m_osc01RangeSliderAttachment = nullptr;
    m_osc01CoarseTuneSliderAttachment = nullptr;
    m_osc01FineTuneSliderAttachment = nullptr;
    m_osc01ModDepthSliderAttachment = nullptr;
    m_osc01ModSourceSliderAttachment = nullptr;
    m_osc01ShapeIntSliderAttachment = nullptr;
    m_osc02RangeSliderAttachment = nullptr;
    m_osc02CoarseTuneSliderAttachment = nullptr;
    m_osc02FineTuneSliderAttachment = nullptr;
    m_osc02ModDepthSliderAttachment = nullptr;
    m_osc02ModSourceSliderAttachment = nullptr;
    m_osc02ShapeIntSliderAttachment = nullptr;

    m_phasor01ShapeSliderAttachment = nullptr;
    m_phasor01EgIntSliderAttachment = nullptr;
    m_phasor01LfoIntSliderAttachment = nullptr;
    m_phasor02ShapeSliderAttachment = nullptr;
    m_phasor02EgIntSliderAttachment = nullptr;
    m_phasor02LfoIntSliderAttachment = nullptr;

    m_mixerOscBalanceSliderAttachment = nullptr;
    m_mixerRingModSliderAttachment = nullptr;
    m_mixerNoiseSliderAttachment = nullptr;

    m_filterCutoffSliderAttachment = nullptr;
    m_filterResoSliderAttachment = nullptr;
    m_filterDriveSliderAttachment = nullptr;
    m_filterModeSliderAttachment = nullptr;
    m_filterEgModDepthSliderAttachment = nullptr;
    m_filterLfoModDepthSliderAttachment = nullptr;

    m_lfo01RateSliderAttachment = nullptr;
    m_lfo01ShapeSliderAttachment = nullptr;
    m_lfo02RateSliderAttachment = nullptr;
    m_lfo02ShapeSliderAttachment = nullptr;

    m_ampEgAtkSliderAttachment = nullptr;
    m_ampEgDecSliderAttachment = nullptr;
    m_ampEgSusSliderAttachment = nullptr;
    m_ampEgRelSliderAttachment = nullptr;

    m_phasorEgAtkSliderAttachment = nullptr;
    m_phasorEgDecSliderAttachment = nullptr;
    m_phasorEgSusSliderAttachment = nullptr;
    m_phasorEgRelSliderAttachment = nullptr;

    m_filterEgAtkSliderAttachment = nullptr;
    m_filterEgDecSliderAttachment = nullptr;
    m_filterEgSusSliderAttachment = nullptr;
    m_filterEgRelSliderAttachment = nullptr;

    m_modEgAtkSliderAttachment = nullptr;
    m_modEgDecSliderAttachment = nullptr;
    m_modEgSusSliderAttachment = nullptr;
    m_modEgRelSliderAttachment = nullptr;
}

void PhantomAudioProcessorEditor::initLayoutVariables()
{    
    textBoxWidth = 80;
    textBoxHeight = 20;
}

void PhantomAudioProcessorEditor::initAmpGui() {
    m_initButton.setButtonText("INIT");
    m_initButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_initButton.onClick = [&]{ reset(); };
    addAndMakeVisible(&m_initButton);

    m_levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_levelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_levelSlider.setTextValueSuffix(" dB");
    m_levelSlider.setDoubleClickReturnValue(true, Consts::_LEVEL_DEFAULT_VAL);
    m_levelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LEVEL_PARAM_ID, m_levelSlider));
    addAndMakeVisible(&m_levelSlider);
    m_levelLabel.setText("Level", dontSendNotification);
    m_levelLabel.setJustificationType(Justification::centred);
    m_levelLabel.attachToComponent(&m_levelSlider, false);
    addAndMakeVisible(&m_levelLabel);
}

void PhantomAudioProcessorEditor::initOscillatorGui() 
{
    m_oscSyncSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscSyncSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscSyncSlider.setDoubleClickReturnValue(true, Consts::_OSC_SYNC_DEFAULT_VAL);
    m_oscSyncSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_SYNC_PARAM_ID, m_oscSyncSlider));
    addAndMakeVisible(&m_oscSyncSlider);
    m_oscSyncLabel.setText("Sync", dontSendNotification);
    m_oscSyncLabel.setJustificationType(Justification::bottomLeft);
    m_oscSyncLabel.attachToComponent(&m_oscSyncSlider, false);
    addAndMakeVisible(&m_oscSyncLabel);

    m_osc01RangeSlider.setSliderStyle(Slider::LinearHorizontal);
    m_osc01RangeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc01RangeSlider.setTextValueSuffix("'");
    m_osc01RangeSlider.setDoubleClickReturnValue(true, Consts::_OSC_01_RANGE_DEFAULT_VAL);
    m_osc01RangeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_RANGE_PARAM_ID, m_osc01RangeSlider));
    addAndMakeVisible(&m_osc01RangeSlider);
    m_osc01RangeLabel.setText("Range", dontSendNotification);
    m_osc01RangeLabel.setJustificationType(Justification::centred);
    m_osc01RangeLabel.attachToComponent(&m_osc01RangeSlider, false);
    addAndMakeVisible(&m_osc01RangeLabel);
    m_oscLabel.setText("Oscillators", dontSendNotification);
    m_oscLabel.setJustificationType(Justification::topLeft);
    m_oscLabel.attachToComponent(&m_osc01RangeSlider, false);
    addAndMakeVisible(&m_oscLabel);

    m_osc01CoarseTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01CoarseTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc01CoarseTuneSlider.setDoubleClickReturnValue(true, Consts::_OSC_01_COARSE_TUNE_DEFAULT_VAL);
    m_osc01CoarseTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_COARSE_TUNE_PARAM_ID, m_osc01CoarseTuneSlider));
    addAndMakeVisible(&m_osc01CoarseTuneSlider);
    m_osc01CoarseTuneLabel.setText("Coarse", dontSendNotification);
    m_osc01CoarseTuneLabel.setJustificationType(Justification::centred);
    m_osc01CoarseTuneLabel.attachToComponent(&m_osc01CoarseTuneSlider, false);
    addAndMakeVisible(&m_osc01CoarseTuneLabel);

    m_osc01FineTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01FineTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc01FineTuneSlider.setDoubleClickReturnValue(true, Consts::_OSC_01_FINE_TUNE_DEFAULT_VAL);
    m_osc01FineTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_FINE_TUNE_PARAM_ID, m_osc01FineTuneSlider));
    addAndMakeVisible(&m_osc01FineTuneSlider);
    m_osc01FineTuneLabel.setText("Fine", dontSendNotification);
    m_osc01FineTuneLabel.setJustificationType(Justification::centred);
    m_osc01FineTuneLabel.attachToComponent(&m_osc01FineTuneSlider, false);
    addAndMakeVisible(&m_osc01FineTuneLabel);

    m_osc01ModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01ModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc01ModDepthSlider.setDoubleClickReturnValue(true, Consts::_OSC_01_MOD_DEPTH_DEFAULT_VAL);
    m_osc01ModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_MOD_DEPTH_PARAM_ID, m_osc01ModDepthSlider));
    addAndMakeVisible(&m_osc01ModDepthSlider);
    m_osc01ModDepthLabel.setText("Mod Depth", dontSendNotification);
    m_osc01ModDepthLabel.setJustificationType(Justification::centred);
    m_osc01ModDepthLabel.attachToComponent(&m_osc01ModDepthSlider, false);
    addAndMakeVisible(&m_osc01ModDepthLabel);

    m_osc01ModSourceSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01ModSourceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc01ModSourceSlider.setDoubleClickReturnValue(true, Consts::_OSC_01_MOD_SOURCE_DEFAULT_VAL);
    m_osc01ModSourceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_MOD_SOURCE_PARAM_ID, m_osc01ModSourceSlider));
    addAndMakeVisible(&m_osc01ModSourceSlider);
    m_osc01ModSourceLabel.setText("Mod Mode", dontSendNotification);
    m_osc01ModSourceLabel.setJustificationType(Justification::centred);
    m_osc01ModSourceLabel.attachToComponent(&m_osc01ModSourceSlider, false);
    addAndMakeVisible(&m_osc01ModSourceLabel);

    m_osc01ShapeIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01ShapeIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc01ShapeIntSlider.setDoubleClickReturnValue(true, Consts::_OSC_01_SHAPE_INT_DEFAULT_VAL);
    m_osc01ShapeIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_SHAPE_INT_PARAM_ID, m_osc01ShapeIntSlider));
    addAndMakeVisible(&m_osc01ShapeIntSlider);
    m_osc01ShapeIntLabel.setText("Shape Int", dontSendNotification);
    m_osc01ShapeIntLabel.setJustificationType(Justification::centred);
    m_osc01ShapeIntLabel.attachToComponent(&m_osc01ShapeIntSlider, false);
    addAndMakeVisible(&m_osc01ShapeIntLabel);

    m_osc02RangeSlider.setSliderStyle(Slider::LinearHorizontal);
    m_osc02RangeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc02RangeSlider.setTextValueSuffix("'");
    m_osc02RangeSlider.setDoubleClickReturnValue(true, Consts::_OSC_02_RANGE_DEFAULT_VAL);
    m_osc02RangeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_RANGE_PARAM_ID, m_osc02RangeSlider));
    addAndMakeVisible(&m_osc02RangeSlider);

    m_osc02CoarseTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02CoarseTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc02CoarseTuneSlider.setDoubleClickReturnValue(true, Consts::_OSC_02_COARSE_TUNE_DEFAULT_VAL);
    m_osc02CoarseTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_COARSE_TUNE_PARAM_ID, m_osc02CoarseTuneSlider));
    addAndMakeVisible(&m_osc02CoarseTuneSlider);

    m_osc02FineTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02FineTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc02FineTuneSlider.setDoubleClickReturnValue(true, Consts::_OSC_02_FINE_TUNE_DEFAULT_VAL);
    m_osc02FineTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_FINE_TUNE_PARAM_ID, m_osc02FineTuneSlider));
    addAndMakeVisible(&m_osc02FineTuneSlider);

    m_osc02ModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02ModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc02ModDepthSlider.setDoubleClickReturnValue(true, Consts::_OSC_02_MOD_DEPTH_DEFAULT_VAL);
    m_osc02ModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_MOD_DEPTH_PARAM_ID, m_osc02ModDepthSlider));
    addAndMakeVisible(&m_osc02ModDepthSlider);

    m_osc02ModSourceSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02ModSourceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc02ModSourceSlider.setDoubleClickReturnValue(true, Consts::_OSC_02_MOD_SOURCE_DEFAULT_VAL);
    m_osc02ModSourceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_MOD_SOURCE_PARAM_ID, m_osc02ModSourceSlider));
    addAndMakeVisible(&m_osc02ModSourceSlider);

    m_osc02ShapeIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02ShapeIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_osc02ShapeIntSlider.setDoubleClickReturnValue(true, Consts::_OSC_02_SHAPE_INT_DEFAULT_VAL);
    m_osc02ShapeIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_SHAPE_INT_PARAM_ID, m_osc02ShapeIntSlider));
    addAndMakeVisible(&m_osc02ShapeIntSlider);
}

void PhantomAudioProcessorEditor::initPhasorGui() 
{
    m_phasor01ShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01ShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasor01ShapeSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_01_SHAPE_DEFAULT_VAL);
    m_phasor01ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_01_SHAPE_PARAM_ID, m_phasor01ShapeSlider));
    addAndMakeVisible(&m_phasor01ShapeSlider);
    m_phasor01ShapeLabel.setText("Shape", dontSendNotification);
    m_phasor01ShapeLabel.setJustificationType(Justification::centred);
    m_phasor01ShapeLabel.attachToComponent(&m_phasor01ShapeSlider, false);
    addAndMakeVisible(&m_phasor01ShapeLabel);
    m_phasorLabel.setText("Phasors", dontSendNotification);
    m_phasorLabel.setJustificationType(Justification::topLeft);
    m_phasorLabel.attachToComponent(&m_phasor01ShapeSlider, false);
    addAndMakeVisible(&m_phasorLabel);

    m_phasor01EgIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01EgIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasor01EgIntSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_01_EG_INT_DEFAULT_VAL);
    m_phasor01EgIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_01_EG_INT_PARAM_ID, m_phasor01EgIntSlider));
    addAndMakeVisible(&m_phasor01EgIntSlider);
    m_phasor01ShapeLabel.setText("EG Int", dontSendNotification);
    m_phasor01ShapeLabel.setJustificationType(Justification::centred);
    m_phasor01ShapeLabel.attachToComponent(&m_phasor01EgIntSlider, false);
    addAndMakeVisible(&m_phasor01ShapeLabel);

    m_phasor01LfoIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01LfoIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasor01LfoIntSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_01_LFO_INT_DEFAULT_VAL);
    m_phasor01LfoIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_01_LFO_INT_PARAM_ID, m_phasor01LfoIntSlider));
    addAndMakeVisible(&m_phasor01LfoIntSlider);
    m_phasor01LfoIntLabel.setText("LFO 2 Int", dontSendNotification);
    m_phasor01LfoIntLabel.setJustificationType(Justification::centred);
    m_phasor01LfoIntLabel.attachToComponent(&m_phasor01LfoIntSlider, false);
    addAndMakeVisible(&m_phasor01LfoIntLabel);

    m_phasor02ShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02ShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasor02ShapeSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_02_SHAPE_DEFAULT_VAL);
    m_phasor02ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_02_SHAPE_PARAM_ID, m_phasor02ShapeSlider));
    addAndMakeVisible(&m_phasor02ShapeSlider);

    m_phasor02EgIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02EgIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasor02EgIntSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_02_EG_INT_DEFAULT_VAL);
    m_phasor02EgIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_02_EG_INT_PARAM_ID, m_phasor02EgIntSlider));
    addAndMakeVisible(&m_phasor02EgIntSlider);

    m_phasor02LfoIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02LfoIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasor02LfoIntSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_02_LFO_INT_DEFAULT_VAL);
    m_phasor02LfoIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_02_LFO_INT_PARAM_ID, m_phasor02LfoIntSlider));
    addAndMakeVisible(&m_phasor02LfoIntSlider);
}

void PhantomAudioProcessorEditor::initMixerGui() 
{
    m_mixerOscBalanceSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerOscBalanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_mixerOscBalanceSlider.setDoubleClickReturnValue(true, Consts::_MIXER_OSC_BAL_DEFAULT_VAL);
    m_mixerOscBalanceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_OSC_BAL_PARAM_ID, m_mixerOscBalanceSlider));
    addAndMakeVisible(&m_mixerOscBalanceSlider);
    m_mixerOscBalanceLabel.setText("Osc Balance", dontSendNotification);
    m_mixerOscBalanceLabel.setJustificationType(Justification::centred);
    m_mixerOscBalanceLabel.attachToComponent(&m_mixerOscBalanceSlider, false);
    addAndMakeVisible(&m_mixerOscBalanceLabel);
    m_mixerLabel.setText("Mixer", dontSendNotification);
    m_mixerLabel.setJustificationType(Justification::topLeft);
    m_mixerLabel.attachToComponent(&m_mixerOscBalanceSlider, false);
    addAndMakeVisible(&m_mixerLabel);

    m_mixerAmpGainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerAmpGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_mixerAmpGainSlider.setDoubleClickReturnValue(true, Consts::_MIXER_AMP_GAIN_DEFAULT_VAL);
    m_mixerAmpGainSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_AMP_GAIN_PARAM_ID, m_mixerAmpGainSlider));
    addAndMakeVisible(&m_mixerAmpGainSlider);
    m_mixerAmpGainLabel.setText("Amp Gain", dontSendNotification);
    m_mixerAmpGainLabel.setJustificationType(Justification::centred);
    m_mixerAmpGainLabel.attachToComponent(&m_mixerAmpGainSlider, false);
    addAndMakeVisible(&m_mixerAmpGainLabel);

    m_mixerRingModSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerRingModSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_mixerRingModSlider.setDoubleClickReturnValue(true, Consts::_MIXER_RING_MOD_DEFAULT_VAL);
    m_mixerRingModSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_RING_MOD_PARAM_ID, m_mixerRingModSlider));
    addAndMakeVisible(&m_mixerRingModSlider);
    m_mixerRingModLabel.setText("Ring Mod", dontSendNotification);
    m_mixerRingModLabel.setJustificationType(Justification::centred);
    m_mixerRingModLabel.attachToComponent(&m_mixerRingModSlider, false);
    addAndMakeVisible(&m_mixerRingModLabel);

    m_mixerNoiseSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerNoiseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_mixerNoiseSlider.setDoubleClickReturnValue(true, Consts::_MIXER_NOISE_DEFAULT_VAL);
    m_mixerNoiseSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_NOISE_PARAM_ID, m_mixerNoiseSlider));
    addAndMakeVisible(&m_mixerNoiseSlider);
    m_mixerNoiseLabel.setText("Noise", dontSendNotification);
    m_mixerNoiseLabel.setJustificationType(Justification::bottomLeft);
    m_mixerNoiseLabel.attachToComponent(&m_mixerNoiseSlider, false);
    addAndMakeVisible(&m_mixerNoiseLabel);
}

void PhantomAudioProcessorEditor::initFilterGui() 
{
    m_filterCutoffSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterCutoffSlider.setTextValueSuffix(" Hz");
    m_filterCutoffSlider.setDoubleClickReturnValue(true, Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterCutoffSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_CUTOFF_PARAM_ID, m_filterCutoffSlider));
    addAndMakeVisible(&m_filterCutoffSlider);
    m_filterCutoffLabel.setText("Cutoff", dontSendNotification);
    m_filterCutoffLabel.setJustificationType(Justification::centred);
    m_filterCutoffLabel.attachToComponent(&m_filterCutoffSlider, false);
    addAndMakeVisible(&m_filterCutoffLabel);
    m_filterLabel.setText("Filter", dontSendNotification);
    m_filterLabel.setJustificationType(Justification::topLeft);
    m_filterLabel.attachToComponent(&m_filterCutoffSlider, false);
    addAndMakeVisible(&m_filterLabel);

    m_filterResoSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterResoSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterResoSlider.setTextValueSuffix(" Q");
    m_filterResoSlider.setDoubleClickReturnValue(true, Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterResoSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_RESO_PARAM_ID, m_filterResoSlider));
    addAndMakeVisible(&m_filterResoSlider);
    m_filterResoLabel.setText("Resonance", dontSendNotification);
    m_filterResoLabel.setJustificationType(Justification::centred);
    m_filterResoLabel.attachToComponent(&m_filterResoSlider, false);
    addAndMakeVisible(&m_filterResoLabel);

    m_filterDriveSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterDriveSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterDriveSlider.setDoubleClickReturnValue(true, Consts::_FLTR_DRIVE_DEFAULT_VAL);
    m_filterDriveSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_DRIVE_PARAM_ID, m_filterDriveSlider));
    addAndMakeVisible(&m_filterDriveSlider);
    m_filterDriveLabel.setText("Drive", dontSendNotification);
    m_filterDriveLabel.setJustificationType(Justification::centred);
    m_filterDriveLabel.attachToComponent(&m_filterDriveSlider, false);
    addAndMakeVisible(&m_filterDriveLabel);

    m_filterModeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterModeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterModeSlider.setDoubleClickReturnValue(true, Consts::_FLTR_MODE_DEFAULT_VAL);
    m_filterModeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_MODE_PARAM_ID, m_filterModeSlider));
    addAndMakeVisible(&m_filterModeSlider);
    m_filterModeLabel.setText("Mode", dontSendNotification);
    m_filterModeLabel.setJustificationType(Justification::centred);
    m_filterModeLabel.attachToComponent(&m_filterModeSlider, false);
    addAndMakeVisible(&m_filterModeLabel);

    m_filterEgModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgModDepthSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterEgModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_MOD_DEPTH_PARAM_ID, m_filterEgModDepthSlider));
    addAndMakeVisible(&m_filterEgModDepthSlider);
    m_filterEgModDepthLabel.setText("EG Depth", dontSendNotification);
    m_filterEgModDepthLabel.setJustificationType(Justification::bottomLeft);
    m_filterEgModDepthLabel.attachToComponent(&m_filterEgModDepthSlider, false);
    addAndMakeVisible(&m_filterEgModDepthLabel);

    m_filterLfoModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterLfoModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterLfoModDepthSlider.setDoubleClickReturnValue(true, Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_LFO_MOD_DEPTH_PARAM_ID, m_filterLfoModDepthSlider));
    addAndMakeVisible(&m_filterLfoModDepthSlider);
    m_filterLfoModDepthLabel.setText("LFO 1 Depth", dontSendNotification);
    m_filterLfoModDepthLabel.setJustificationType(Justification::bottomLeft);
    m_filterLfoModDepthLabel.attachToComponent(&m_filterLfoModDepthSlider, false);
    addAndMakeVisible(&m_filterLfoModDepthLabel);
}

void PhantomAudioProcessorEditor::initLfoGui()
{
    m_lfo01RateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01RateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_lfo01RateSlider.setTextValueSuffix(" Hz");
    m_lfo01RateSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01RateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_01_RATE_PARAM_ID, m_lfo01RateSlider));
    addAndMakeVisible(&m_lfo01RateSlider);
    m_lfo01RateLabel.setText("Rate", dontSendNotification);
    m_lfo01RateLabel.setJustificationType(Justification::centred);
    m_lfo01RateLabel.attachToComponent(&m_lfo01RateSlider, false);
    addAndMakeVisible(&m_lfo01RateLabel);
    m_lfoLabel.setText("LFOs", dontSendNotification);
    m_lfoLabel.setJustificationType(Justification::topLeft);
    m_lfoLabel.attachToComponent(&m_lfo01RateSlider, false);
    addAndMakeVisible(&m_lfoLabel);

    m_lfo01ShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01ShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_lfo01ShapeSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo01ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_01_SHAPE_PARAM_ID, m_lfo01ShapeSlider));
    addAndMakeVisible(&m_lfo01ShapeSlider);
    m_lfo01ShapeLabel.setText("Shape", dontSendNotification);
    m_lfo01ShapeLabel.setJustificationType(Justification::centred);
    m_lfo01ShapeLabel.attachToComponent(&m_lfo01ShapeSlider, false);
    addAndMakeVisible(&m_lfo01ShapeLabel);

    m_lfo02RateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02RateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_lfo02RateSlider.setTextValueSuffix(" Hz");
    m_lfo02RateSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo02RateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_02_RATE_PARAM_ID, m_lfo02RateSlider));
    addAndMakeVisible(&m_lfo02RateSlider);

    m_lfo02ShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02ShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_lfo02ShapeSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo02ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_02_SHAPE_PARAM_ID, m_lfo02ShapeSlider));
    addAndMakeVisible(&m_lfo02ShapeSlider);
}

void PhantomAudioProcessorEditor::initEgGui() 
{
    m_ampEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgAtkSlider.setTextValueSuffix(" s");
    m_ampEgAtkSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_ATK_PARAM_ID, m_ampEgAtkSlider));
    addAndMakeVisible(&m_ampEgAtkSlider);
    m_ampEgAtkLabel.setText("Atk", dontSendNotification);
    m_ampEgAtkLabel.setJustificationType(Justification::centred);
    m_ampEgAtkLabel.attachToComponent(&m_ampEgAtkSlider, false);
    addAndMakeVisible(&m_ampEgAtkLabel);
    m_ampEgLabel.setText("AMP", dontSendNotification);
    m_ampEgLabel.setJustificationType(Justification::right);
    m_ampEgLabel.attachToComponent(&m_ampEgAtkSlider, true);
    addAndMakeVisible(&m_ampEgLabel);

    m_ampEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgDecSlider.setTextValueSuffix(" s");
    m_ampEgDecSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_DEC_PARAM_ID, m_ampEgDecSlider));
    addAndMakeVisible(&m_ampEgDecSlider);
    m_ampEgDecLabel.setText("Dec", dontSendNotification);
    m_ampEgDecLabel.setJustificationType(Justification::centred);
    m_ampEgDecLabel.attachToComponent(&m_ampEgDecSlider, false);
    addAndMakeVisible(&m_ampEgDecLabel);

    m_ampEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgSusSlider.setTextValueSuffix(" dB");
    m_ampEgSusSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_SUS_PARAM_ID, m_ampEgSusSlider));
    addAndMakeVisible(&m_ampEgSusSlider);
    m_ampEgSusLabel.setText("Sus", dontSendNotification);
    m_ampEgSusLabel.setJustificationType(Justification::centred);
    m_ampEgSusLabel.attachToComponent(&m_ampEgSusSlider, false);
    addAndMakeVisible(&m_ampEgSusLabel);

    m_ampEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgRelSlider.setTextValueSuffix(" s");
    m_ampEgRelSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_REL_DEFAULT_VAL);
    m_ampEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_REL_PARAM_ID, m_ampEgRelSlider));
    addAndMakeVisible(&m_ampEgRelSlider);
    m_ampEgRelLabel.setText("Rel", dontSendNotification);
    m_ampEgRelLabel.setJustificationType(Justification::centred);
    m_ampEgRelLabel.attachToComponent(&m_ampEgRelSlider, false);
    addAndMakeVisible(&m_ampEgRelLabel);

    m_phasorEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgAtkSlider.setTextValueSuffix(" s");
    m_phasorEgAtkSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_ATK_PARAM_ID, m_phasorEgAtkSlider));
    addAndMakeVisible(&m_phasorEgAtkSlider);
    m_phasorEgAtkLabel.setText("Atk", dontSendNotification);
    m_phasorEgAtkLabel.setJustificationType(Justification::centred);
    m_phasorEgAtkLabel.attachToComponent(&m_phasorEgAtkSlider, false);
    addAndMakeVisible(&m_phasorEgAtkLabel);
    m_phasorEgLabel.setText("PHA", dontSendNotification);
    m_phasorEgLabel.setJustificationType(Justification::right);
    m_phasorEgLabel.attachToComponent(&m_phasorEgAtkSlider, true);
    addAndMakeVisible(&m_phasorEgLabel);

    m_phasorEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgDecSlider.setTextValueSuffix(" s");
    m_phasorEgDecSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_DEC_PARAM_ID, m_phasorEgDecSlider));
    addAndMakeVisible(&m_phasorEgDecSlider);
    m_phasorEgDecLabel.setText("Dec", dontSendNotification);
    m_phasorEgDecLabel.setJustificationType(Justification::centred);
    m_phasorEgDecLabel.attachToComponent(&m_phasorEgDecSlider, false);
    addAndMakeVisible(&m_phasorEgDecLabel);

    m_phasorEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgSusSlider.setTextValueSuffix(" dB");
    m_phasorEgSusSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_SUS_PARAM_ID, m_phasorEgSusSlider));
    addAndMakeVisible(&m_phasorEgSusSlider);
    m_phasorEgSusLabel.setText("Sus", dontSendNotification);
    m_phasorEgSusLabel.setJustificationType(Justification::centred);
    m_phasorEgSusLabel.attachToComponent(&m_phasorEgSusSlider, false);
    addAndMakeVisible(&m_phasorEgSusLabel);

    m_phasorEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgRelSlider.setTextValueSuffix(" s");
    m_phasorEgRelSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_REL_DEFAULT_VAL);
    m_phasorEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_REL_PARAM_ID, m_phasorEgRelSlider));
    addAndMakeVisible(&m_phasorEgRelSlider);
    m_phasorEgRelLabel.setText("Rel", dontSendNotification);
    m_phasorEgRelLabel.setJustificationType(Justification::centred);
    m_phasorEgRelLabel.attachToComponent(&m_phasorEgRelSlider, false);
    addAndMakeVisible(&m_phasorEgRelLabel);

    m_filterEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgAtkSlider.setTextValueSuffix(" s");
    m_filterEgAtkSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_ATK_PARAM_ID, m_filterEgAtkSlider));
    addAndMakeVisible(&m_filterEgAtkSlider);
    m_filterEgLabel.setText("FLTR", dontSendNotification);
    m_filterEgLabel.setJustificationType(Justification::right);
    m_filterEgLabel.attachToComponent(&m_filterEgAtkSlider, true);
    addAndMakeVisible(&m_filterEgLabel);

    m_filterEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgDecSlider.setTextValueSuffix(" s");
    m_filterEgDecSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_DEC_PARAM_ID, m_filterEgDecSlider));
    addAndMakeVisible(&m_filterEgDecSlider);

    m_filterEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgSusSlider.setTextValueSuffix(" dB");
    m_filterEgSusSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_SUS_PARAM_ID, m_filterEgSusSlider));
    addAndMakeVisible(&m_filterEgSusSlider);

    m_filterEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgRelSlider.setTextValueSuffix(" s");
    m_filterEgRelSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_REL_DEFAULT_VAL);
    m_filterEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_REL_PARAM_ID, m_filterEgRelSlider));
    addAndMakeVisible(&m_filterEgRelSlider);

    m_modEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_modEgAtkSlider.setTextValueSuffix(" s");
    m_modEgAtkSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_ATK_PARAM_ID, m_modEgAtkSlider));
    addAndMakeVisible(&m_modEgAtkSlider);
    m_modEgLabel.setText("MOD", dontSendNotification);
    m_modEgLabel.setJustificationType(Justification::right);
    m_modEgLabel.attachToComponent(&m_modEgAtkSlider, true);
    addAndMakeVisible(&m_modEgLabel);

    m_modEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_modEgDecSlider.setTextValueSuffix(" s");
    m_modEgDecSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_DEC_DEFAULT_VAL);
    m_modEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_DEC_PARAM_ID, m_modEgDecSlider));
    addAndMakeVisible(&m_modEgDecSlider);

    m_modEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_modEgSusSlider.setTextValueSuffix(" dB");
    m_modEgSusSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_SUS_DEFAULT_VAL);
    m_modEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_SUS_PARAM_ID, m_modEgSusSlider));
    addAndMakeVisible(&m_modEgSusSlider);

    m_modEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_modEgRelSlider.setTextValueSuffix(" s");
    m_modEgRelSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_REL_DEFAULT_VAL);
    m_modEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_REL_PARAM_ID, m_modEgRelSlider));
    addAndMakeVisible(&m_modEgRelSlider);
}

void PhantomAudioProcessorEditor::initOscilloscope()
{
    m_oscilloscope = std::make_unique<PhantomOscilloscope>();

    addAndMakeVisible(m_oscilloscope.get());
}

void PhantomAudioProcessorEditor::initAnalyzer() 
{
    m_analyzer = std::make_unique<PhantomAnalyzer>();

    addAndMakeVisible(m_analyzer.get());
}

void PhantomAudioProcessorEditor::initPresetMenu()
{
    m_presetLabel.setText("PRESET: ", dontSendNotification);
    m_presetLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&m_presetLabel);

    m_presetButton.setButtonText("preset_name");
    addAndMakeVisible(&m_presetButton);

    m_presetButton.onClick = [this](){
        PopupMenu menu;

        menu.addItem(PopupMenu::Item("Save as")
            .setAction([this](){
                DBG("Saving as ...");
            })
        );
        menu.addItem(PopupMenu::Item("Copy to clipboard")
            .setAction([this](){
                SystemClipboard::copyTextToClipboard(*m_processor.saveStateToText());
            })
        );
        menu.addItem(PopupMenu::Item("Paste from clipboard")
            .setAction([this](){
                DBG("Pasting ...");
            })
        );

        menu.addSeparator();

        // // TODO: Add submenus here for bass, pads, ..., and user

        // // TODO: Load presets from XML here...
        // String dataDir = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
        //     + "/Black Box DSP/Phantom";
        // DBG(dataDir);

        // File dir(dataDir);
        // if(!dir.exists())
        //     dir.createDirectory();

        // Array<File> files = dir.findChildFiles(File::findFiles, false, "*.xml");
        // for(File f : files)
        // {
        //     DBG("FILE: " << f.getFileName());
        // }

        // if(dir.getChildFile("presets.xml").existsAsFile())
        // {
        //     DBG("presets.xml does exist");
        // }
        // else 
        // {
        //     DBG("presets.xml does NOT exist");
        // }

        menu.show();
    };
}

void PhantomAudioProcessorEditor::reset()
{
    m_levelSlider.setValue(Consts::_LEVEL_DEFAULT_VAL);

    m_oscSyncSlider.setValue(Consts::_OSC_SYNC_DEFAULT_VAL);
    m_osc01RangeSlider.setValue(Consts::_OSC_01_RANGE_DEFAULT_VAL);
    m_osc01CoarseTuneSlider.setValue(Consts::_OSC_01_COARSE_TUNE_DEFAULT_VAL);
    m_osc01FineTuneSlider.setValue(Consts::_OSC_01_FINE_TUNE_DEFAULT_VAL);
    m_osc01ShapeIntSlider.setValue(Consts::_OSC_01_SHAPE_INT_DEFAULT_VAL);
    m_osc01ModDepthSlider.setValue(Consts::_OSC_01_MOD_DEPTH_DEFAULT_VAL);
    m_osc01ModSourceSlider.setValue(Consts::_OSC_01_MOD_SOURCE_DEFAULT_VAL);
    m_osc02RangeSlider.setValue(Consts::_OSC_02_RANGE_DEFAULT_VAL);
    m_osc02CoarseTuneSlider.setValue(Consts::_OSC_02_COARSE_TUNE_DEFAULT_VAL);
    m_osc02FineTuneSlider.setValue(Consts::_OSC_02_FINE_TUNE_DEFAULT_VAL);
    m_osc02ShapeIntSlider.setValue(Consts::_OSC_02_SHAPE_INT_DEFAULT_VAL);
    m_osc02ModDepthSlider.setValue(Consts::_OSC_02_MOD_DEPTH_DEFAULT_VAL);
    m_osc02ModSourceSlider.setValue(Consts::_OSC_02_MOD_SOURCE_DEFAULT_VAL);

    m_phasor01ShapeSlider.setValue(Consts::_PHASOR_01_SHAPE_DEFAULT_VAL);
    m_phasor01EgIntSlider.setValue(Consts::_PHASOR_01_EG_INT_DEFAULT_VAL);
    m_phasor01LfoIntSlider.setValue(Consts::_PHASOR_01_LFO_INT_DEFAULT_VAL);
    m_phasor02ShapeSlider.setValue(Consts::_PHASOR_02_SHAPE_DEFAULT_VAL);
    m_phasor02EgIntSlider.setValue(Consts::_PHASOR_02_EG_INT_DEFAULT_VAL);
    m_phasor02LfoIntSlider.setValue(Consts::_PHASOR_02_LFO_INT_DEFAULT_VAL);

    m_mixerOscBalanceSlider.setValue(Consts::_MIXER_OSC_BAL_DEFAULT_VAL);
    m_mixerAmpGainSlider.setValue(Consts::_MIXER_AMP_GAIN_DEFAULT_VAL);
    m_mixerRingModSlider.setValue(Consts::_MIXER_RING_MOD_DEFAULT_VAL);
    m_mixerNoiseSlider.setValue(Consts::_MIXER_NOISE_DEFAULT_VAL);

    m_filterCutoffSlider.setValue(Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterResoSlider.setValue(Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterDriveSlider.setValue(Consts::_FLTR_DRIVE_DEFAULT_VAL);
    m_filterModeSlider.setValue(Consts::_FLTR_MODE_DEFAULT_VAL);
    m_filterEgModDepthSlider.setValue(Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSlider.setValue(Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);

    m_lfo01RateSlider.setValue(Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01ShapeSlider.setValue(Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo02RateSlider.setValue(Consts::_LFO_02_RATE_DEFAULT_VAL);
    m_lfo02ShapeSlider.setValue(Consts::_LFO_02_SHAPE_DEFAULT_VAL);

    m_ampEgAtkSlider.setValue(Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgDecSlider.setValue(Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgSusSlider.setValue(Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgRelSlider.setValue(Consts::_AMP_EG_REL_DEFAULT_VAL);

    m_filterEgAtkSlider.setValue(Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgDecSlider.setValue(Consts::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgSusSlider.setValue(Consts::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgRelSlider.setValue(Consts::_FLTR_EG_REL_DEFAULT_VAL);

    m_phasorEgAtkSlider.setValue(Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgDecSlider.setValue(Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgSusSlider.setValue(Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgRelSlider.setValue(Consts::_PHASOR_EG_REL_DEFAULT_VAL);

    m_modEgAtkSlider.setValue(Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgDecSlider.setValue(Consts::_MOD_EG_DEC_DEFAULT_VAL);
    m_modEgSusSlider.setValue(Consts::_MOD_EG_SUS_DEFAULT_VAL);
    m_modEgRelSlider.setValue(Consts::_MOD_EG_REL_DEFAULT_VAL);
}

void PhantomAudioProcessorEditor::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomAudioProcessorEditor::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    const int margin = canvas.getWidth() / 60;
    canvas.removeFromTop(margin);
    canvas.removeFromRight(margin);
    canvas.removeFromBottom(margin);
    canvas.removeFromLeft(margin);

    const int width = canvas.getWidth();
    const int height = canvas.getHeight();
    const int sectionHeight = (height - (margin * 6)) / 4;

    const int topKnobWidth = (width - margin) / 7;
    Rectangle<int> topArea = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    Rectangle<int> ampArea = topArea.removeFromLeft(topKnobWidth);
    topArea.removeFromLeft(margin);
    ampArea.removeFromLeft(margin * 3);
    ampArea.removeFromRight(margin * 3);

    m_levelSlider.setBounds(ampArea.removeFromBottom(ampArea.getHeight() / 2));

    ampArea.removeFromBottom(margin * 1.5);

    m_initButton.setBounds(ampArea);

    Rectangle<int> oscillatorArea = topArea;

    Rectangle<int> oscillatorRangeArea = oscillatorArea.removeFromLeft(topKnobWidth);
    const int oscillatorAreaSixthHeight = oscillatorArea.getHeight() / 6;
    m_osc01RangeSlider.setBounds(oscillatorRangeArea.removeFromTop(oscillatorAreaSixthHeight * 1.5));
    m_oscSyncSlider.setBounds(oscillatorRangeArea.removeFromTop(oscillatorAreaSixthHeight * 3));
    m_osc02RangeSlider.setBounds(oscillatorRangeArea);

    Rectangle<int> oscillator01Area = oscillatorArea.removeFromTop(oscillatorArea.getHeight() / 2);
    m_osc01CoarseTuneSlider.setBounds(oscillator01Area.removeFromLeft(topKnobWidth));
    m_osc01FineTuneSlider.setBounds(oscillator01Area.removeFromLeft(topKnobWidth));
    m_osc01ShapeIntSlider.setBounds(oscillator01Area.removeFromLeft(topKnobWidth));
    m_osc01ModDepthSlider.setBounds(oscillator01Area.removeFromLeft(topKnobWidth));
    m_osc01ModSourceSlider.setBounds(oscillator01Area);

    Rectangle<int> oscillator02Area = oscillatorArea;
    m_osc02CoarseTuneSlider.setBounds(oscillator02Area.removeFromLeft(topKnobWidth));
    m_osc02FineTuneSlider.setBounds(oscillator02Area.removeFromLeft(topKnobWidth));
    m_osc02ShapeIntSlider.setBounds(oscillator02Area.removeFromLeft(topKnobWidth));
    m_osc02ModDepthSlider.setBounds(oscillator02Area.removeFromLeft(topKnobWidth));
    m_osc02ModSourceSlider.setBounds(oscillator02Area);

    const int middleTopKnobWidth = (width - (margin * 2)) / 7;
    Rectangle<int> middleTopArea = canvas.removeFromTop(sectionHeight + (margin * 2));
    canvas.removeFromTop(margin);

    Rectangle<int> oscilloscopeArea = middleTopArea.removeFromLeft(middleTopKnobWidth * 2);
    middleTopArea.removeFromLeft(margin);
    m_oscilloscope->setBounds(oscilloscopeArea);

    Rectangle<int> phasorArea = middleTopArea.removeFromLeft(middleTopKnobWidth * 3);
    middleTopArea.removeFromLeft(margin);

    Rectangle<int> presetArea = phasorArea.removeFromBottom(margin * 1.5);
    m_presetLabel.setBounds(presetArea.removeFromLeft(presetArea.getWidth() / 2));
    m_presetButton.setBounds(presetArea);
    phasorArea.removeFromBottom(margin * 0.5);

    Rectangle<int> phasor01Area = phasorArea.removeFromTop(phasorArea.getHeight() / 2);
    m_phasor01ShapeSlider.setBounds(phasor01Area.removeFromLeft(middleTopKnobWidth));
    m_phasor01EgIntSlider.setBounds(phasor01Area.removeFromLeft(middleTopKnobWidth));
    m_phasor01LfoIntSlider.setBounds(phasor01Area);

    Rectangle<int> phasor02Area = phasorArea;
    m_phasor02ShapeSlider.setBounds(phasor02Area.removeFromLeft(middleTopKnobWidth));
    m_phasor02EgIntSlider.setBounds(phasor02Area.removeFromLeft(middleTopKnobWidth));
    m_phasor02LfoIntSlider.setBounds(phasor02Area);

    Rectangle<int> analyzerArea = middleTopArea;
    m_analyzer->setBounds(analyzerArea);

    const int middleBottomKnobWidth = (width - (margin * 2)) / 7;
    Rectangle<int> middleBottomArea = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    Rectangle<int> mixerArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 2);
    middleBottomArea.removeFromLeft(margin);

    Rectangle<int> mixerTopArea = mixerArea.removeFromTop(mixerArea.getHeight() / 2);
    m_mixerOscBalanceSlider.setBounds(mixerTopArea.removeFromLeft(middleTopKnobWidth));
    m_mixerRingModSlider.setBounds(mixerTopArea);

    Rectangle<int> mixerBottomArea = mixerArea;
    m_mixerAmpGainSlider.setBounds(mixerBottomArea.removeFromLeft(middleTopKnobWidth));
    m_mixerNoiseSlider.setBounds(mixerBottomArea);

    Rectangle<int> filterArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 3);
    middleBottomArea.removeFromLeft(margin);

    Rectangle<int> filterTopArea = filterArea.removeFromTop(filterArea.getHeight() / 2);
    m_filterCutoffSlider.setBounds(filterTopArea.removeFromLeft(middleBottomKnobWidth));
    m_filterResoSlider.setBounds(filterTopArea.removeFromLeft(middleBottomKnobWidth));
    m_filterDriveSlider.setBounds(filterTopArea);

    Rectangle<int> filterBottomArea = filterArea;
    m_filterModeSlider.setBounds(filterBottomArea.removeFromLeft(middleBottomKnobWidth));
    m_filterEgModDepthSlider.setBounds(filterBottomArea.removeFromLeft(middleBottomKnobWidth));
    m_filterLfoModDepthSlider.setBounds(filterBottomArea);

    Rectangle<int> lfoArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 2);
    Rectangle<int> lfoTopArea = lfoArea.removeFromTop(lfoArea.getHeight() / 2);
    m_lfo01RateSlider.setBounds(lfoTopArea.removeFromLeft(middleBottomKnobWidth));
    m_lfo01ShapeSlider.setBounds(lfoTopArea);

    Rectangle<int> lfoBottomArea = lfoArea;
    m_lfo02RateSlider.setBounds(lfoBottomArea.removeFromLeft(middleBottomKnobWidth));
    m_lfo02ShapeSlider.setBounds(lfoBottomArea);

    const int bottomKnobWidth = (width - (margin * 2)) / 8;
    Rectangle<int> bottomArea = canvas;

    Rectangle<int> bottomTopArea = bottomArea.removeFromTop(bottomArea.getHeight() / 2);
    Rectangle<int> ampEgArea = bottomTopArea.removeFromLeft(bottomKnobWidth * 4);
    bottomTopArea.removeFromLeft(margin);
    m_ampEgAtkSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));
    m_ampEgDecSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));
    m_ampEgSusSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));
    m_ampEgRelSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));

    Rectangle<int> phasorEgArea = bottomTopArea;
    m_phasorEgAtkSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));
    m_phasorEgDecSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));
    m_phasorEgSusSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));
    m_phasorEgRelSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));

    Rectangle<int> bottomBottomArea = bottomArea;
    Rectangle<int> filterEgArea = bottomBottomArea.removeFromLeft(bottomKnobWidth * 4);
    bottomBottomArea.removeFromLeft(margin);
    m_filterEgAtkSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));
    m_filterEgDecSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));
    m_filterEgSusSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));
    m_filterEgRelSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));

    Rectangle<int> modEgArea = bottomBottomArea;
    m_modEgAtkSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
    m_modEgDecSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
    m_modEgSusSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
    m_modEgRelSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
}

void print_something()
{
    std::cout << "SOMETHING" << std::endl;
}
