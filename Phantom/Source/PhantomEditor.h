#pragma once

#include <JuceHeader.h>
#include "PhantomProcessor.h"

//==============================================================================
/**
*/
class PhantomAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor&);
    ~PhantomAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhantomAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)
};
