/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

//==============================================================================
#include "processor.h"
#include "editor.h"

//==============================================================================
PhantomAudioProcessorEditor::PhantomAudioProcessorEditor (PhantomAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
}

//==============================================================================
void PhantomAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::deepskyblue);
}

void PhantomAudioProcessorEditor::resized()
{
    // TODO: layout components here
}
