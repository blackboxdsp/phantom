/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"
#include "PhantomProcessor.h"
#include "PhantomUtils.h"

//==============================================================================
PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), m_audioProcessor(p), m_parameters(vts)
{
    const int textBoxWidth = 80;
    const int textBoxHeight = 20;

    //==========================================================================

    // OSCILLATOR

    m_oscRangeSlider.setSliderStyle(Slider::LinearVertical);
    m_oscRangeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscRangeSlider.setTextValueSuffix("'");
    m_oscRangeSlider.setDoubleClickReturnValue(true, Consts::_OSC_RANGE_DEFAULT_VAL);
    m_oscRangeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_RANGE_PARAM_ID, m_oscRangeSlider));
    addAndMakeVisible(&m_oscRangeSlider);

    m_oscTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscTuneSlider.setDoubleClickReturnValue(true, Consts::_OSC_TUNE_DEFAULT_VAL);
    m_oscTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_TUNE_PARAM_ID, m_oscTuneSlider));
    addAndMakeVisible(&m_oscTuneSlider);

    m_oscModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscModDepthSlider.setDoubleClickReturnValue(true, Consts::_OSC_MOD_DEPTH_DEFAULT_VAL);
    m_oscModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_MOD_DEPTH_PARAM_ID, m_oscModDepthSlider));
    addAndMakeVisible(&m_oscModDepthSlider);

    // PHASOR

    m_phasorShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorShapeSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_SHAPE_DEFAULT_VAL);
    m_phasorShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_SHAPE_PARAM_ID, m_phasorShapeSlider));
    addAndMakeVisible(&m_phasorShapeSlider);

    m_phasorEgIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgIntSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_INT_DEFAULT_VAL);
    m_phasorEgIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_INT_PARAM_ID, m_phasorEgIntSlider));
    addAndMakeVisible(&m_phasorEgIntSlider);

    m_phasorLfoIntSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorLfoIntSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorLfoIntSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_LFO_INT_DEFAULT_VAL);
    m_phasorLfoIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_LFO_INT_PARAM_ID, m_phasorLfoIntSlider));
    addAndMakeVisible(&m_phasorLfoIntSlider);

    // FILTER

    m_filterCutoffSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterCutoffSlider.setTextValueSuffix(" Hz");
    m_filterCutoffSlider.setDoubleClickReturnValue(true, Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterCutoffSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_CUTOFF_PARAM_ID, m_filterCutoffSlider));
    addAndMakeVisible(&m_filterCutoffSlider);

    m_filterResoSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterResoSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterResoSlider.setTextValueSuffix(" Q");
    m_filterResoSlider.setDoubleClickReturnValue(true, Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterResoSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_RESO_PARAM_ID, m_filterResoSlider));
    addAndMakeVisible(&m_filterResoSlider);

    m_filterEgModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgModDepthSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterEgModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_MOD_DEPTH_PARAM_ID, m_filterEgModDepthSlider));
    addAndMakeVisible(&m_filterEgModDepthSlider);

    m_filterLfoModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterLfoModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterLfoModDepthSlider.setDoubleClickReturnValue(true, Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_LFO_MOD_DEPTH_PARAM_ID, m_filterLfoModDepthSlider));
    addAndMakeVisible(&m_filterLfoModDepthSlider);
    
    // AMP EG

    m_ampEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgAtkSlider.setTextValueSuffix(" s");
    m_ampEgAtkSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_ATK_PARAM_ID, m_ampEgAtkSlider));
    addAndMakeVisible(&m_ampEgAtkSlider);

    m_ampEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgDecSlider.setTextValueSuffix(" s");
    m_ampEgDecSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_DEC_PARAM_ID, m_ampEgDecSlider));
    addAndMakeVisible(&m_ampEgDecSlider);

    m_ampEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgSusSlider.setTextValueSuffix(" dB");
    m_ampEgSusSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_SUS_PARAM_ID, m_ampEgSusSlider));
    addAndMakeVisible(&m_ampEgSusSlider);

    m_ampEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgRelSlider.setTextValueSuffix(" s");
    m_ampEgRelSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_REL_DEFAULT_VAL);
    m_ampEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_REL_PARAM_ID, m_ampEgRelSlider));
    addAndMakeVisible(&m_ampEgRelSlider);

    // PHASOR EG

    m_phasorEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgAtkSlider.setTextValueSuffix(" s");
    m_phasorEgAtkSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_ATK_PARAM_ID, m_phasorEgAtkSlider));
    addAndMakeVisible(&m_phasorEgAtkSlider);

    m_phasorEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgDecSlider.setTextValueSuffix(" s");
    m_phasorEgDecSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_DEC_PARAM_ID, m_phasorEgDecSlider));
    addAndMakeVisible(&m_phasorEgDecSlider);

    m_phasorEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgSusSlider.setTextValueSuffix(" dB");
    m_phasorEgSusSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_SUS_PARAM_ID, m_phasorEgSusSlider));
    addAndMakeVisible(&m_phasorEgSusSlider);

    m_phasorEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_phasorEgRelSlider.setTextValueSuffix(" s");
    m_phasorEgRelSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_REL_DEFAULT_VAL);
    m_phasorEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_REL_PARAM_ID, m_phasorEgRelSlider));
    addAndMakeVisible(&m_phasorEgRelSlider);

    // FILTER EG

    m_filterEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgAtkSlider.setTextValueSuffix(" s");
    m_filterEgAtkSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_ATK_PARAM_ID, m_filterEgAtkSlider));
    addAndMakeVisible(&m_filterEgAtkSlider);

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

    // MOD EG

    m_modEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_modEgAtkSlider.setTextValueSuffix(" s");
    m_modEgAtkSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_ATK_PARAM_ID, m_modEgAtkSlider));
    addAndMakeVisible(&m_modEgAtkSlider);

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

    // LFO

    m_lfoRateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfoRateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_lfoRateSlider.setTextValueSuffix(" Hz");
    m_lfoRateSlider.setDoubleClickReturnValue(true, Consts::_LFO_RATE_DEFAULT_VAL);
    m_lfoRateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_RATE_PARAM_ID, m_lfoRateSlider));
    addAndMakeVisible(&m_lfoRateSlider);

    m_lfoShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfoShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_lfoShapeSlider.setDoubleClickReturnValue(true, Consts::_LFO_SHAPE_DEFAULT_VAL);
    m_lfoShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_SHAPE_PARAM_ID, m_lfoShapeSlider));
    addAndMakeVisible(&m_lfoShapeSlider);

    // AMP

    m_levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_levelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_levelSlider.setTextValueSuffix(" dB");
    m_levelSlider.setDoubleClickReturnValue(true, Consts::_LEVEL_DEFAULT_VAL);
    m_levelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LEVEL_PARAM_ID, m_levelSlider));
    addAndMakeVisible(&m_levelSlider);

    //==========================================================================
    setResizable(true, true);
    setSize(720, 540);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    m_oscRangeSliderAttachment = nullptr;
    m_oscTuneSliderAttachment = nullptr;
    m_oscModDepthSliderAttachment = nullptr;

    m_phasorShapeSliderAttachment = nullptr;
    m_phasorEgIntSliderAttachment = nullptr;
    m_phasorLfoIntSliderAttachment = nullptr;

    m_filterCutoffSliderAttachment = nullptr;
    m_filterResoSliderAttachment = nullptr;
    m_filterEgModDepthSliderAttachment = nullptr;
    m_filterLfoModDepthSliderAttachment = nullptr;

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

    m_lfoRateSliderAttachment = nullptr;
    m_lfoShapeSliderAttachment = nullptr;

    m_levelSliderAttachment = nullptr;
}

//==============================================================================
void PhantomAudioProcessorEditor::paint(Graphics& g)
{
    // Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.setFont(15.0f);
}

void PhantomAudioProcessorEditor::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    int margin = getWidth() / 30;
    canvas.removeFromTop(margin);
    canvas.removeFromRight(margin);
    canvas.removeFromBottom(margin);
    canvas.removeFromLeft(margin);

    int width = canvas.getWidth();
    int height = canvas.getHeight();

    int knobWidth;

    //==========================================================================
    Rectangle<int> top =  canvas.removeFromTop(height / 5);
    knobWidth = width / 10;

    Rectangle<int> oscArea = top.removeFromLeft(5 * knobWidth);
    m_oscRangeSlider.setBounds(oscArea.removeFromLeft(knobWidth));
    m_oscTuneSlider.setBounds(oscArea.removeFromLeft(knobWidth));
    m_oscModDepthSlider.setBounds(oscArea.removeFromLeft(knobWidth));

    Rectangle<int> phasorArea = top.removeFromLeft(3 * knobWidth);
    m_phasorShapeSlider.setBounds(phasorArea.removeFromLeft(knobWidth));
    m_phasorEgIntSlider.setBounds(phasorArea.removeFromLeft(knobWidth));
    m_phasorLfoIntSlider.setBounds(phasorArea);

    Rectangle<int> lfoArea = top.removeFromLeft(2 * knobWidth);
    m_lfoRateSlider.setBounds(lfoArea.removeFromLeft(knobWidth));
    m_lfoShapeSlider.setBounds(lfoArea);

    //==========================================================================
    Rectangle<int> middle = canvas.removeFromTop(2 * height / 5);
    knobWidth = width / 8;
    
    Rectangle<int> filterArea = middle.removeFromLeft(3 * knobWidth);
    Rectangle<int> filterAreaTop = filterArea.removeFromTop(height / 5);
    m_filterCutoffSlider.setBounds(filterAreaTop.removeFromLeft(knobWidth));
    m_filterResoSlider.setBounds(filterAreaTop.removeFromLeft(knobWidth));
    m_filterEgModDepthSlider.setBounds(filterArea.removeFromLeft(knobWidth * 1.5));
    m_filterLfoModDepthSlider.setBounds(filterArea);
    
    Rectangle<int> utilityArea = middle.removeFromLeft(3 * knobWidth);

    Rectangle<int> ampArea = middle.removeFromLeft(2 * knobWidth);
    ampArea.removeFromLeft(knobWidth / 2);
    ampArea.removeFromRight(knobWidth / 2);
    m_levelSlider.setBounds(ampArea);

    //==========================================================================
    Rectangle<int> bottom = canvas;
    Rectangle<int> bottomTop = bottom.removeFromTop(height / 5);
    
    m_ampEgAtkSlider.setBounds(bottomTop.removeFromLeft(knobWidth));
    m_ampEgDecSlider.setBounds(bottomTop.removeFromLeft(knobWidth));
    m_ampEgSusSlider.setBounds(bottomTop.removeFromLeft(knobWidth));
    m_ampEgRelSlider.setBounds(bottomTop.removeFromLeft(knobWidth));

    m_phasorEgAtkSlider.setBounds(bottomTop.removeFromLeft(knobWidth));
    m_phasorEgDecSlider.setBounds(bottomTop.removeFromLeft(knobWidth));
    m_phasorEgSusSlider.setBounds(bottomTop.removeFromLeft(knobWidth));
    m_phasorEgRelSlider.setBounds(bottomTop);

    m_filterEgAtkSlider.setBounds(bottom.removeFromLeft(knobWidth));
    m_filterEgDecSlider.setBounds(bottom.removeFromLeft(knobWidth));
    m_filterEgSusSlider.setBounds(bottom.removeFromLeft(knobWidth));
    m_filterEgRelSlider.setBounds(bottom.removeFromLeft(knobWidth));

    m_modEgAtkSlider.setBounds(bottom.removeFromLeft(knobWidth));
    m_modEgDecSlider.setBounds(bottom.removeFromLeft(knobWidth));
    m_modEgSusSlider.setBounds(bottom.removeFromLeft(knobWidth));
    m_modEgRelSlider.setBounds(bottom);
}
