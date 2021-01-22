/*
  ==============================================================================

    PhantomVoice.h
    Created: 20 Jan 2021 8:59:55pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomOscillator.h"
#include "PhantomEnvelopeGenerator.h"

//==============================================================================
/**
*/
class PhantomVoice : public SynthesiserVoice
{
public:
    //==========================================================================
    PhantomVoice(AudioProcessorValueTreeState&);
    ~PhantomVoice();

    //==========================================================================
    bool canPlaySound(SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override;

    void stopNote(float velocity, bool allowTailOff) override;

    //==========================================================================
    void pitchWheelMoved(int newPitchWheel) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    //==========================================================================
    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples) override;

    //==========================================================================
    float midiNoteToFrequency(float midiNote);

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomVoice)

    //==========================================================================
    forcedinline void updateOscillator() noexcept;

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_oscRange;
    std::atomic<float>* p_oscTune;

    //==========================================================================
    int m_midiNoteNumber = 60;
    
    PhantomOscillator* m_osc;
    PhantomEnvelopeGenerator* m_ampEg;
};
