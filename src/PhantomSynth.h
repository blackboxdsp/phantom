/*
  ==============================================================================

    PhantomSynth.h
    Created: 21 Jan 2021 10:45:00
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/**
 * The synthesizer class for Phantom.
 */
class PhantomSynth : public Synthesiser
{
public:
    PhantomSynth(AudioProcessorValueTreeState&);
    ~PhantomSynth() override;

    /**
     * Initializes the synthesizer parameters.
     * @param sampleRate The sample rate to use in setting phase deltas / frequencies.
     * @param samplesPerBlock The number of samples in a block (audio buffer).
     * @param numChannels The number of channels to use in the processing.
     * @param playHead The audio play head object from the audio processor.
     */
    void init(float sampleRate, int samplesPerBlock, int numChannels, AudioPlayHead* playHead);

    /**
     * Clears sounds and voices from the synthesizer.
     */
    void clear();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomSynth)

    /**
     * Adds voices to the synthesizer object.
     * @param playHead The audio play head object from the audio processor.
     */
    void addVoices(AudioPlayHead* playHead);

    /**
     * Adds sounds to the synthesizer object.
     */
    void addSounds();

    /**
     * The `ProcessSpec` to use in applying calculations 
     * from JUCE's DSP modules.
     */
    dsp::ProcessSpec m_processSpec;
  
    AudioProcessorValueTreeState& m_parameters;

    /**
     * The number of voices to use in the synth.
     */
    const int k_numVoices = 1;
};
