/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomProcessor.h"

//==============================================================================
/**
*/
class PhantomAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor&);
    ~PhantomAudioProcessorEditor() override;

    //==========================================================================
    void paint(Graphics&) override;
    void resized() override;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhantomAudioProcessor& m_audioProcessor;
};
