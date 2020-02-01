/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PhantomProcessor.h"
#include "PhantomEditor.h"

//==============================================================================
PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (960, 540);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
}

//==============================================================================
void PhantomAudioProcessorEditor::paint (Graphics& g)
{
}

void PhantomAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}