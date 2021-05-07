/*
  ==============================================================================

    PhantomPresetManager.h
    Created: 06 May 2021 15:12:05
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_PRESET_MANAGER_H
#define _PHANTOM_PRESET_MANAGER_H

#include "JuceHeader.h"

/**
 * The manager class for things related to presets, including parameters and state data.
 * CAUTION: This class is intended to be created from within processor and NOTHING else. If 
 * it is required elsewhere, use a reference.
 */
class PhantomPresetManager
{
public:
    PhantomPresetManager(AudioProcessorValueTreeState& vts);
    ~PhantomPresetManager();

    /**
     * Re-initializes variables relevant variables for plugin state data. 
     * NOTE: This method does NOT have to be called prior to any other functionality 
     * being used.
     */
    void init();

    /**
     * Loads the presets' filepaths from the presets
     * directory.
     */
    void loadPresetFilePaths();

    /**
     * Loads the file in the filepaths array at the specified index.
     * @param increment If true, will increment the index and decrement otherwise.
     */
    void loadPresetFile(bool increment);

    /**
     * Sets the preset index based on the preset files 
     * in the presets folder and the current name according 
     * to the processor.
     * @returns `true` if a preset was matched.
     */
    bool setPresetIdx();
    
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
     * @param file The reference to the `File` containing the state data to load.
     */
    void loadStateFromFile(File& file);

    /**
     * Looks at the preset name variable and returns its value.
     * @returns The currently set preset name, defualt is "Init".
     */
    String getCurrentPresetName();

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

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomPresetManager);

    /**
     * The unique pointer to the `AudioProcessorValueTreeState` object, containing all of the plugin
     * state data.
     */
    AudioProcessorValueTreeState& m_parameters;

    /**
     * The name of the currently selected preset.
     */
    String m_presetName;

    /**
     * This array holds all of the relative paths to the presets in 
     * the same order they were added to the preset menu (alphabetically).
     */
    Array<String> m_presetFilePaths;

    /**
     * This index keeps track of the currently selected preset's
     * filepath, using for navigating quickly between them.
     * WARNING: Do NOT change the initialization value of -3.
     */
    int m_presetIdx = -3;
};

AudioProcessorValueTreeState::ParameterLayout CreateParameterLayout();

#endif
