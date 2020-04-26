/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

//==============================================================================
#pragma once

#include <JuceHeader.h>

#include "processor.h"

//==============================================================================
class PhantomAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    //==========================================================================
    PhantomAudioProcessorEditor (PhantomAudioProcessor&);
    ~PhantomAudioProcessorEditor();

    //==========================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==========================================================================
    PhantomAudioProcessor& processor;

    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhantomAudioProcessorEditor)
};
