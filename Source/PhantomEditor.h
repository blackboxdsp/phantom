/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "PhantomOscilloscope.h"
#include "PhantomProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class PhantomAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor&, AudioProcessorValueTreeState&);
    ~PhantomAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==========================================================================
    std::unique_ptr<PhantomOscilloscope> phaseOscilloscope;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhantomAudioProcessor& processor;

    AudioProcessorValueTreeState& parameters;

    OpenGLContext glContext;

    const Colour primaryColour = Colour::fromRGBA(78, 152, 212, 255);

    // COMPONENTS ==============================================================


    // PHASE DISTORTION
    Slider                              phaseIdSlider;
    std::unique_ptr<SliderAttachment>   phaseIdAttachment;
    Slider                              phaseIntensitySlider;
    std::unique_ptr<SliderAttachment>   phaseIntensityAttachment;

    // ADSR 
    Slider                              attackSlider;
    std::unique_ptr<SliderAttachment>   attackAttachment;
    Slider                              decaySlider;
    std::unique_ptr<SliderAttachment>   decayAttachment;
    Slider                              sustainSlider;
    std::unique_ptr<SliderAttachment>   sustainAttachment;
    Slider                              releaseSlider;
    std::unique_ptr<SliderAttachment>   releaseAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhantomAudioProcessorEditor)
};
