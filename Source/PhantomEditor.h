/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhantomAudioProcessor& processor;

    AudioProcessorValueTreeState& parameters;

    OpenGLContext glContext;

    // COMPONENTS ==============================================================

    // PHASE DISTORTION
    Slider                              phaseOffsetSlider;
    std::unique_ptr<SliderAttachment>   phaseOffsetAttachment;

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
