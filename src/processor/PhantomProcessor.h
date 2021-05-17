/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#ifndef _PHANTOM_PROCESSOR_H
#define _PHANTOM_PROCESSOR_H

#include "JuceHeader.h"

#include "../effects/PhantomAmplifier.h"
#include "PhantomSynth.h"
#include "PhantomPresetManager.h"
#include "../utils/PhantomUtils.h"

/**
 * The audio processor component, containing the important JUCE boilerplate 
 * code for the plugin.
 */
class PhantomAudioProcessor : public AudioProcessor
{
public:
    PhantomAudioProcessor();
    ~PhantomAudioProcessor() override;

    /**
     * Called before playback starts, to let the processor prepare itself (i.e. initialize the synth)
     */
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    /**
     * Called after playback has stopped, to let the object free up any resources
     * it no longer needs.
     */
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    /**
     * Callback to query if the `AudioProcessor` supports a specific layout.
     */
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    /**
     * Renders the next block.
     */
    void processBlock(AudioBuffer<float> &, MidiBuffer &) override;

    /**
     * Returns true if the processor has a corresponding editor.
     */
    bool hasEditor() const override;

    /**
     * Creates the processor's GUI.
     */ 
    AudioProcessorEditor *createEditor() override;

    /**
     * Gets the name of the plugin, which is defined in the utilities header file.
     */
    const String getName() const override;

    /**
     * Returns true if the processor wants MIDI messages.
     */
    bool acceptsMidi() const override;

    /**
     * Returns true if the processor produces MIDI messages.
     */
    bool producesMidi() const override;
    
    /**
     * Returns true if this is a MIDI effect plugin and does not process audio.
     */
    bool isMidiEffect() const override;

    /**
     * Returns the length of the processor's tail, in seconds.
     */
    double getTailLengthSeconds() const override;

    /**
     * Returns the number of preset programs the processor supports.
     * NOTE: I designed a cross-platform system so this isn't that relevant.
     */
    int getNumPrograms() override;

    /**
     * Returns the number of the currently active program.
     */
    int getCurrentProgram() override;
    
    /**
     * Called by the host to change the current program.
     */
    void setCurrentProgram(int index) override;
    
    /**
     * Returns the name of a given program.
     */
    const String getProgramName(int index) override;
    
    /**
     * Called by the host to rename a program.
     */
    void changeProgramName(int index, const String &newName) override;

    /**
     * Stores state information (XML data) in a binary format.
     * @param destData The reference to the block of memory to store the data.
     */
    void getStateInformation(MemoryBlock &destData) override;

    /**
     * Retrieves state information from binary data.
     * @param data The block of memory to read from.
     * @param sizeInBytes The size of the block of memory in bytes.
     */
    void setStateInformation(const void *data, int sizeInBytes) override;

    /**
     * Corresponds to the current preset manager of the processor.
     * @returns A reference of the current preset manager object.
     */
    PhantomPresetManager& getPresetManager();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessor)

    /**
     * The object holding all of the plugin state date (aka parameter values).
     */
    AudioProcessorValueTreeState m_parameters;

    /**
     * The preset manager responsible for all things preset-related (non-GUI).
     */
    std::unique_ptr<PhantomPresetManager> m_presetManager;

    /**
     * The synthesizer object pointer that renders blocks from the processor.
     */
    std::unique_ptr<PhantomSynth> m_synth;

    /**
     * The amplifier that applies gain to the buffer after the synthesizer 
     * has written its data.
     */
    std::unique_ptr<PhantomAmplifier> m_amp;
};

#endif
