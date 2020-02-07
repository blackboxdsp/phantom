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

    // PHASE ID
    phaseIdSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    phaseIdSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    phaseIdSlider.setDoubleClickReturnValue(true, 0);
    phaseIdAttachment.reset(new SliderAttachment(parameters, "phaseId", phaseIdSlider));
    addAndMakeVisible(&phaseIdSlider);

    // ATTACK
    attackSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    attackSlider.setTextValueSuffix(" s");
    attackSlider.setDoubleClickReturnValue(true, 0.001f);
    attackAttachment.reset(new SliderAttachment(parameters, "attack", attackSlider));
    addAndMakeVisible(&attackSlider);

    // DECAY
    decaySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    decaySlider.setTextValueSuffix(" s");
    decaySlider.setDoubleClickReturnValue(true, 0.6f);
    decayAttachment.reset(new SliderAttachment(parameters, "decay", decaySlider));
    addAndMakeVisible(&decaySlider);

    // SUSTAIN
    sustainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    sustainSlider.setTextValueSuffix(" dB");
    sustainSlider.setDoubleClickReturnValue(true, 0.0f);
    sustainAttachment.reset(new SliderAttachment(parameters, "sustain", sustainSlider));
    addAndMakeVisible(&sustainSlider);

    // RELEASE
    releaseSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    releaseSlider.setTextValueSuffix(" s");
    releaseSlider.setDoubleClickReturnValue(true, 0.05f);
    releaseAttachment.reset(new SliderAttachment(parameters, "release", releaseSlider));
    addAndMakeVisible(&releaseSlider);

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
    attackAttachment = nullptr;
    decayAttachment = nullptr;
    sustainAttachment = nullptr;
    releaseAttachment = nullptr;
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

    // ADSR
    auto adsrRect = canvas.removeFromBottom(canvas.getHeight() / 2);
    attackSlider.setBounds(adsrRect.removeFromLeft(smallDialSize));
    decaySlider.setBounds(adsrRect.removeFromLeft(smallDialSize));
    sustainSlider.setBounds(adsrRect.removeFromLeft(smallDialSize));
    releaseSlider.setBounds(adsrRect.removeFromLeft(smallDialSize));

    // PHASE DISTORTION
    auto phaseRect = canvas;
    phaseIdSlider.setBounds(phaseRect);
}
