/*
  ==============================================================================

    PhantomSynth.h
    Created: 31 Jan 2020 9:33:53pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class PhantomSynthSound : public SynthesiserSound
{
public:
    PhantomSynthSound()     {}
    ~PhantomSynthSound()    {}

    bool appliesToNote      (int) override { return true; }
    bool appliesToChannel   (int) override { return true; }
};

//==============================================================================
class PhantomSynthVoice : public SynthesiserVoice
{
public:
    PhantomSynthVoice();
    ~PhantomSynthVoice();

    bool canPlaySound       (SynthesiserSound* sound)                                                                       override;
    void controllerMoved    (int controllerNumber, int newControllerValue)                                                  override;
    void pitchWheelMoved    (int newPitchWheelValue)                                                                        override;
    void renderNextBlock    (AudioSampleBuffer& buffer, int startSample, int numSamples)                                    override;
    void startNote          (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)    override;
    void stopNote           (float velocity, bool allowTailOff)                                                             override;

private:
    double currentPhase = 0.0, level = 0.0, phaseDelta = 0.0, tailOff = 0.0;
};

//==============================================================================
class PhantomSynthAudioSource : public AudioSource
{
public:
    PhantomSynthAudioSource(MidiKeyboardState& keyState);
    ~PhantomSynthAudioSource();

    void getNextAudioBlock          (const AudioSourceChannelInfo& bufferToFill)    override;
    void prepareToPlay              (int samplesPerBlock, double sampleRate)        override;
    void releaseResources           ()                                              override;
    void setUsingPhantomSynthSound  ();

private:
    MidiKeyboardState& keyboardState;
    Synthesiser synth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhantomSynthAudioSource)
};
