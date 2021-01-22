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
    m_oscRangeSlider.setSliderStyle(Slider::LinearVertical);
    m_oscRangeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscRangeSlider.setTextValueSuffix("'");
    m_oscRangeSlider.setDoubleClickReturnValue(true, 2);
    m_oscRangeSliderAttachment.reset(new SliderAttachment(m_parameters, Parameters::_OSC_RANGE_PARAM_ID, m_oscRangeSlider));
    addAndMakeVisible(&m_oscRangeSlider);

    m_oscTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscTuneSlider.setDoubleClickReturnValue(true, 0.0f);
    m_oscTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Parameters::_OSC_TUNE_PARAM_ID, m_oscTuneSlider));
    addAndMakeVisible(&m_oscTuneSlider);

    m_levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_levelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_levelSlider.setTextValueSuffix(" dB");
    m_levelSlider.setDoubleClickReturnValue(true, 0.0f);
    m_levelSliderAttachment.reset(new SliderAttachment(m_parameters, Parameters::_LEVEL_PARAM_ID, m_levelSlider));
    addAndMakeVisible(&m_levelSlider);

    //==========================================================================
    setSize(540, 360);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    m_oscRangeSliderAttachment = nullptr;
    m_oscTuneSliderAttachment = nullptr;

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

    int width = getWidth();

    Rectangle<int> left = canvas.removeFromLeft(width / 3);
    m_oscRangeSlider.setBounds(left);

    Rectangle<int> middle = canvas.removeFromLeft(width / 3);
    m_oscTuneSlider.setBounds(middle);

    Rectangle<int> right = canvas;
    m_levelSlider.setBounds(right);
}
