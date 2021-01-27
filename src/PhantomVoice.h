/*
  ==============================================================================

    PhantomVoice.h
    Created: 20 Jan 2021 20:59:55
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomAmplifier.h"
#include "PhantomEnvelopeGenerator.h"
#include "PhantomFilter.h"
#include "PhantomOscillator.h"

//==============================================================================
/**
*/
class PhantomVoice : public SynthesiserVoice
{
public:
    //==========================================================================
    PhantomVoice(AudioProcessorValueTreeState&, dsp::ProcessSpec&);
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

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomVoice)

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    //==========================================================================
    // NOTE: 60 corresponds to middle C
    int m_midiNoteNumber = 60;
    
    PhantomEnvelopeGenerator* m_ampEg;
    PhantomEnvelopeGenerator* m_phaseEg;
    PhantomEnvelopeGenerator* m_filterEg;
    PhantomEnvelopeGenerator* m_modEg;
    
    PhantomOscillator* m_osc;
    PhantomFilter* m_filter;
    PhantomAmplifier* m_amp;
};
