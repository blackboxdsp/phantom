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
    m_oscRangeSlider.setDoubleClickReturnValue(true, Params::_OSC_RANGE_DEFAULT_VAL);
    m_oscRangeSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_OSC_RANGE_PARAM_ID, m_oscRangeSlider));
    addAndMakeVisible(&m_oscRangeSlider);

    m_oscTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscTuneSlider.setDoubleClickReturnValue(true, Params::_OSC_TUNE_DEFAULT_VAL);
    m_oscTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_OSC_TUNE_PARAM_ID, m_oscTuneSlider));
    addAndMakeVisible(&m_oscTuneSlider);

    // AMP EG

    m_ampEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgAtkSlider.setTextValueSuffix(" s");
    m_ampEgAtkSlider.setDoubleClickReturnValue(true, Params::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_AMP_EG_ATK_PARAM_ID, m_ampEgAtkSlider));
    addAndMakeVisible(&m_ampEgAtkSlider);

    m_ampEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgDecSlider.setTextValueSuffix(" s");
    m_ampEgDecSlider.setDoubleClickReturnValue(true, Params::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_AMP_EG_DEC_PARAM_ID, m_ampEgDecSlider));
    addAndMakeVisible(&m_ampEgDecSlider);

    m_ampEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgSusSlider.setTextValueSuffix(" dB");
    m_ampEgSusSlider.setDoubleClickReturnValue(true, Params::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_AMP_EG_SUS_PARAM_ID, m_ampEgSusSlider));
    addAndMakeVisible(&m_ampEgSusSlider);

    m_ampEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_ampEgRelSlider.setTextValueSuffix(" s");
    m_ampEgRelSlider.setDoubleClickReturnValue(true, Params::_AMP_EG_REL_DEFAULT_VAL);
    m_ampEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_AMP_EG_REL_PARAM_ID, m_ampEgRelSlider));
    addAndMakeVisible(&m_ampEgRelSlider);

    // FILTER EG

    m_filterEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgAtkSlider.setTextValueSuffix(" s");
    m_filterEgAtkSlider.setDoubleClickReturnValue(true, Params::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_FLTR_EG_ATK_PARAM_ID, m_filterEgAtkSlider));
    addAndMakeVisible(&m_filterEgAtkSlider);

    m_filterEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgDecSlider.setTextValueSuffix(" s");
    m_filterEgDecSlider.setDoubleClickReturnValue(true, Params::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_FLTR_EG_DEC_PARAM_ID, m_filterEgDecSlider));
    addAndMakeVisible(&m_filterEgDecSlider);

    m_filterEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgSusSlider.setTextValueSuffix(" dB");
    m_filterEgSusSlider.setDoubleClickReturnValue(true, Params::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_FLTR_EG_SUS_PARAM_ID, m_filterEgSusSlider));
    addAndMakeVisible(&m_filterEgSusSlider);

    m_filterEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterEgRelSlider.setTextValueSuffix(" s");
    m_filterEgRelSlider.setDoubleClickReturnValue(true, Params::_FLTR_EG_REL_DEFAULT_VAL);
    m_filterEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_FLTR_EG_REL_PARAM_ID, m_filterEgRelSlider));
    addAndMakeVisible(&m_filterEgRelSlider);

    // FILTER

    m_filterCutoffSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterCutoffSlider.setTextValueSuffix(" Hz");
    m_filterCutoffSlider.setDoubleClickReturnValue(true, Params::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterCutoffSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_FLTR_CUTOFF_PARAM_ID, m_filterCutoffSlider));
    addAndMakeVisible(&m_filterCutoffSlider);

    m_filterResoSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterResoSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_filterResoSlider.setTextValueSuffix(" Q");
    m_filterResoSlider.setDoubleClickReturnValue(true, Params::_FLTR_RESO_DEFAULT_VAL);
    m_filterResoSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_FLTR_RESO_PARAM_ID, m_filterResoSlider));
    addAndMakeVisible(&m_filterResoSlider);

    // AMP

    m_levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_levelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_levelSlider.setTextValueSuffix(" dB");
    m_levelSlider.setDoubleClickReturnValue(true, Params::_LEVEL_DEFAULT_VAL);
    m_levelSliderAttachment.reset(new SliderAttachment(m_parameters, Params::_LEVEL_PARAM_ID, m_levelSlider));
    addAndMakeVisible(&m_levelSlider);

    //==========================================================================
    setSize(720, 480);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    m_oscRangeSliderAttachment = nullptr;
    m_oscTuneSliderAttachment = nullptr;

    m_ampEgAtkSliderAttachment = nullptr;
    m_ampEgDecSliderAttachment = nullptr;
    m_ampEgSusSliderAttachment = nullptr;
    m_ampEgRelSliderAttachment = nullptr;

    m_filterEgAtkSliderAttachment = nullptr;
    m_filterEgDecSliderAttachment = nullptr;
    m_filterEgSusSliderAttachment = nullptr;
    m_filterEgRelSliderAttachment = nullptr;

    m_filterCutoffSliderAttachment = nullptr;
    m_filterResoSliderAttachment = nullptr;

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

    // TOP

    Rectangle<int> top = canvas.removeFromTop(height / 2);

    m_oscRangeSlider.setBounds(top.removeFromLeft(width / 5));
    m_oscTuneSlider.setBounds(top.removeFromLeft(width / 5));

    m_filterCutoffSlider.setBounds(top.removeFromLeft(width / 5));
    m_filterResoSlider.setBounds(top.removeFromLeft(width / 5));

    m_levelSlider.setBounds(top);

    // BOTTOM
    Rectangle<int> bottomTop = canvas.removeFromTop(canvas.getHeight() / 2);

    m_ampEgAtkSlider.setBounds(bottomTop.removeFromLeft(width / 4));
    m_ampEgDecSlider.setBounds(bottomTop.removeFromLeft(width / 4));
    m_ampEgSusSlider.setBounds(bottomTop.removeFromLeft(width / 4));
    m_ampEgRelSlider.setBounds(bottomTop);

    Rectangle<int> bottomBottom = canvas;

    m_filterEgAtkSlider.setBounds(bottomBottom.removeFromLeft(width / 4));
    m_filterEgDecSlider.setBounds(bottomBottom.removeFromLeft(width / 4));
    m_filterEgSusSlider.setBounds(bottomBottom.removeFromLeft(width / 4));
    m_filterEgRelSlider.setBounds(bottomBottom);
}
