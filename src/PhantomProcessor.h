/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomAmplifier.h"
#include "PhantomSynth.h"
#include "PhantomUtils.h"

/**
 * The audio processor component, containing the important JUCE boilerplate 
 * code for the plugin.
 */
class PhantomAudioProcessor : public AudioProcessor
{
public:
    PhantomAudioProcessor();
    ~PhantomAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(AudioBuffer<float> &, MidiBuffer &) override;

    AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
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
     * Saves all plugin metadata data to the XML element.
     * @param xml The reference to the XML object to save to.
     */
    void saveMetadataToXml(XmlElement& xml);

    /**
     * Loads all plugin data (+ parameters) from the XML element.
     * @param xml The XML object to load state data from.
     */
    void loadStateFromXml(XmlElement& xml);
    
    /**
     * Loads XML data in string format from memory at specified reference.
     * @param stateStr The reference to the memory of the string-formatted XML data.
     */ 
    void loadStateFromText(const String& stateStr);

    /**
     * Saves XML data in string format to memory at specified reference.
     * @param destStr The reference to the intended destination of the string-formatted XML data.
     */ 
    void saveStateToText(String& destStr);


    void loadStateFromFile(File newFile);
    

    bool saveStateToFile(File newFile);

    /**
     * Calculates the skew factor given a start, end, and desired center point.
     * @param start The start value to use.
     * @param end The end value to use.
     * @param center The value to skew to the middle.
     */
    float getSkewFactor(float start, float end, float center);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessor)

    AudioProcessorValueTreeState m_parameters;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    /**
     * The synthesizer object pointer that renders blocks from the processor.
     */
    std::unique_ptr<PhantomSynth> m_synth;

    /**
     * The amplifier that applies gain to the buffer after the synthesizer 
     * has written its data.
     */
    std::unique_ptr<PhantomAmplifier> m_amp;

    /**
     * The name of the currently selected preset.
     */
    String m_presetName;

    /**
     * The name of the plugin.
     */
    const String k_pluginName = "Phantom";

    /**
     * The version of the plugin.
     */
    const String k_pluginVersion = "1.0.0-beta";

    /**
     * The total number of parameters.
     */
    const int k_numParameters = 50;
};
