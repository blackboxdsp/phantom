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

    bool hasEditor() const override;
    AudioProcessorEditor *createEditor() override;

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
     * Loads plugin state from the XML element.
     * @param xml The XML object to load state data from.
     * @returns The same pointer provided to the method.
     */
    std::unique_ptr<XmlElement> loadStateFromXml(std::unique_ptr<XmlElement> xml);

    /**
     * Saves all plugin metadata data to the XML element (i.e. version, preset name).
     * @param xml The reference to the XML object to save to.
     * @returns The same pointer provided to the method.
     */
    std::unique_ptr<XmlElement> saveMetadataToXml(std::unique_ptr<XmlElement> xml);

    /**
     * Saves all plugin metadata data to the XML element (i.e. version, preset name).
     * @param xml The reference to the XML object to save to.
     * @param presetName The preset name to use.
     * @returns The same pointer provided to the method.
     */
    std::unique_ptr<XmlElement> saveMetadataToXml(std::unique_ptr<XmlElement> xml, String& presetName);

    /**
     * Saves XML data in string format to memory at specified reference.
     * @returns Pointer to the `String` object containing all of the state data.
     */ 
    std::unique_ptr<String> saveStateToText();
    
    /**
     * Loads XML data in string format from memory at specified reference.
     * @param stateStr The reference to the memory of the string-formatted XML data.
     */ 
    void loadStateFromText(const String& stateStr);

    /**
     * Creates or overwrites preset file containing the plugin state data in XML format.
     * @param file The reference to the file to save data to.
     * @returns `true` if the file was saved successfully.
     */
    bool saveStateToFile(File& file);

    /**
     * Creates or overwrites preset file data from XML.
     * @param xml The pointer to the XmlElement to write as a file.
     * @param dir The reference to the directory to save the file.
     * @returns `true` if the file was saved successfully.
     */
    bool saveXmlToFile(std::unique_ptr<XmlElement> xml, File& dir);
    
    /**
     * Loads the plugin state data from a preset file.
     */
    void loadStateFromFile(File& file);

    /**
     * Retrieves the appropriate preset directory for the user, whether it exists or not.
     * @returns The file object representing the preset folder on the user's machine.
     */
    File getPresetDirectory();

    /**
     * Retrieves all of the preset files (*.xml) within the presets folder.
     */
    Array<File> getPresetFiles();

    /**
     * Writes all of the (XML) binary data resources
     * to files the app data directory on the user's computer.
     * CAUTION: Be sure to precompile the binary resources if you've added more stock presets.
     * @returns `true` if the file was saved successfully.
     */
    void writePresetFiles(); 

    /**
     * Re-initializes variables relevant variables for
     * plugin state data.
     */
    void resetState();

    /**
     * Calculates the skew factor given a start, end, and desired center point.
     * @param start The start value to use.
     * @param end The end value to use.
     * @param center The value to skew to the middle.
     */
    float getSkewFactor(float start, float end, float center);

    /**
     * The name of the currently selected preset.
     */
    String m_presetName = String("Init");

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
};
