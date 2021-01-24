/*
  ==============================================================================

    PhantomSynth.h
    Created: 21 Jan 2021 10:45:00
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomSynth : public Synthesiser
{
public:
    //==========================================================================
    PhantomSynth(AudioProcessorValueTreeState&);
    ~PhantomSynth() override;

    //==========================================================================
    void init(float sampleRate, int samplesPerBlock, int numChannels);
    void clear();

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomSynth)

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    dsp::ProcessSpec m_processSpec;

    //==========================================================================
    void addVoices();
    void addSounds();

    //==========================================================================
    const int k_numVoices = 1;
};
