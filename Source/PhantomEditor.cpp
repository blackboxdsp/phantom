/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PhantomProcessor.h"
#include "PhantomEditor.h"

//==============================================================================
PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), 
      processor (p),
      parameters(vts)
{
    // GUI variables
    int textBoxWidth = 80;
    int textBoxHeight = 20;

    // LEVEL
    levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelSlider.setTextBoxStyle(Slider::NoTextBox, false, textBoxWidth, textBoxHeight);
    levelSlider.setTextValueSuffix(" dB");
    levelSlider.setDoubleClickReturnValue(true, 0.0f);
    levelAttachment.reset(new SliderAttachment(parameters, "level", levelSlider));
    addAndMakeVisible(&levelSlider);

    //==========================================================================

    // handle open gl initializing
    glContext.setComponentPaintingEnabled(true);
    glContext.attachTo(*this);

    // set aspect ratio and dimensions accordingly
    double ratio = 2.0;
    int minWidth = 1280, maxWidth = 1920;
    setResizeLimits(minWidth, minWidth / ratio, maxWidth, maxWidth / ratio);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(minWidth, minWidth / ratio);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    // handle gl context
    glContext.detach();

    // nullify component attachments
    levelAttachment = nullptr;
}

//==============================================================================
void PhantomAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkblue);
}

void PhantomAudioProcessorEditor::resized()
{
    // get max canvas area
    auto canvas = getLocalBounds();

    // set layout variables
    auto margin = getWidth() / 30;
    auto largeDialSize = getWidth() * 13 / 45;
    auto smallDialSize = getWidth() * 13 / 60;

    // remove margins
    canvas.removeFromBottom(margin);
    canvas.removeFromLeft(margin);
    canvas.removeFromRight(margin);
    canvas.removeFromTop(margin);

    // LEVEL
    levelSlider.setBounds(canvas);
}
