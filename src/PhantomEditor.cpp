/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"
#include "PhantomProcessor.h"

//==============================================================================
PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), m_audioProcessor(p), m_parameters(vts)
{
    const int textBoxWidth = 80;
    const int textBoxHeight = 20;

    //==========================================================================
    m_oscillatorRangeSlider.setSliderStyle(Slider::LinearVertical);
    m_oscillatorRangeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscillatorRangeSlider.setDoubleClickReturnValue(true, 2);
    m_oscillatorRangeSliderAttachment.reset(new SliderAttachment(m_parameters, "oscillatorRange", m_oscillatorRangeSlider));
    addAndMakeVisible(&m_oscillatorRangeSlider);

    m_oscillatorTuneSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscillatorTuneSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_oscillatorTuneSlider.setTextValueSuffix(" Semi");
    m_oscillatorTuneSlider.setDoubleClickReturnValue(true, 0.0f);
    m_oscillatorTuneSliderAttachment.reset(new SliderAttachment(m_parameters, "oscillatorTune", m_oscillatorTuneSlider));
    addAndMakeVisible(&m_oscillatorTuneSlider);

    m_levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_levelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    m_levelSlider.setTextValueSuffix(" dB");
    m_levelSlider.setDoubleClickReturnValue(true, 0.0f);
    m_levelSliderAttachment.reset(new SliderAttachment(m_parameters, "level", m_levelSlider));
    addAndMakeVisible(&m_levelSlider);

    //==========================================================================
    setSize(540, 360);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    m_oscillatorRangeSliderAttachment = nullptr;
    m_oscillatorTuneSliderAttachment = nullptr;

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
    m_oscillatorRangeSlider.setBounds(left);

    Rectangle<int> middle = canvas.removeFromLeft(width / 3);
    m_oscillatorTuneSlider.setBounds(middle);

    Rectangle<int> right = canvas;
    m_levelSlider.setBounds(right);
}
