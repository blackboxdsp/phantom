/*
  ==============================================================================

    PhantomOscillator.h
    Created: 20 Jan 2021 21:17:28
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomOscillator 
{
public:
    //==========================================================================
    PhantomOscillator(AudioProcessorValueTreeState&);
    ~PhantomOscillator();

    //==========================================================================
    void update(int midiNoteNumber, float sampleRate);

    float getNextSample();

    float midiNoteToFrequency(float midiNote);

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscillator)

    //==========================================================================
    void initParameters();
    void initWavetable();

    void setPhaseDelta(float frequency, float sampleRate);
    
    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_oscRange;
    std::atomic<float>* p_oscTune;

    //==========================================================================
    Array<float> m_wavetable;
    const int k_wavetableSize = 1 << 11;

    float m_phase = 0.0;
    float m_phaseDelta = 0.0;

    int m_midiNoteNumber;
    float m_frequency;
    float m_sampleRate;
};
