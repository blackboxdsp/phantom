/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#ifndef _PHANTOM_EDITOR_H
#define _PHANTOM_EDITOR_H

#include "JuceHeader.h"

#include "PhantomLookAndFeel.h"
#include "../components/PhantomAmplifier.h"
#include "../components/PhantomAnalyzer.h"
#include "../components/PhantomEnvelope.h"
#include "../components/PhantomFilter.h"
#include "../components/PhantomLFO.h"
#include "../components/PhantomMixer.h"
#include "../components/PhantomOscillator.h"
#include "../components/PhantomOscilloscope.h"
#include "../components/PhantomPhasor.h"
#include "../processor/PhantomProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

/**
 * The editor component holding most of the code responsible for the
 * GUI (sliders, buttons, text, etc.).
 */
class PhantomAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PhantomAudioProcessorEditor() override;

    /**
     * Determines the appearance of the main plugin component.
     */
    void paint(Graphics &) override;

    /**
     * Determines the layout of the various GUI components for new 
     * window size.
     */
    void resized() override;

    /**
     * Adds presets from presets folder to popup menu.
     * @param menu The reference to the menu to add the presets to.
     */
    void addPresetsToMenu(PopupMenu &menu);

    /**
     * Loads the presets' filepaths from the presets 
     * directory.
     */
    void loadPresetFilePaths();

    /**
     * Loads the file in the filepaths array at the specified index.
     */
    void loadPresetFileAtIndex();

    /**
     * Sets the preset index based on the preset files 
     * in the presets folder and the current name according 
     * to the processor.
     * @returns `true` if a preset was matched.
     */
    bool setPresetIdx();

    /**
     * Resets components of the GUI.
     */
    void resetGui();

    /**
     * Resets all of the sliders to their default values, useful for 
     * initializing new synth patches.
     */
    void resetParameters();

    /**
     * This reference is provided as a quick way for your editor to
     * access the processor object that created it.
     */
    PhantomAudioProcessor &m_processor;

    /**
     * The unique pointer to the analyzer, used by the processor.
     */
    std::unique_ptr<PhantomAnalyzerComponent> m_phantomAnalyzer;

    /**
     * The unique pointer to the oscilloscope, used by the processor.
     */
    std::unique_ptr<PhantomOscilloscopeComponent> m_phantomOscilloscope;

    /** The reference to the value tree state useful in retrieving or 
     * storing parameter information.
     */
    AudioProcessorValueTreeState &m_parameters;

    /**
     * This array holds all of the relative paths to the presets in 
     * the same order they were added to the preset menu (alphabetically).
     */
    Array<String> m_presetFilePaths;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)

    /**
     * Initializes the GUI for the preset menu.
     */
    void initPresetMenu();

    /** Initializes the editor component. */
    void initEditor();

    /**
     * This index keeps track of the currently selected preset's
     * filepath, using for navigating quickly between them.
     * WARNING: Do NOT change the initialization value.
     */
    int m_presetIdx = -3;

    /** The custom look and feel for the plugin. */
    PhantomLookAndFeel m_lookAndFeel;

    /** GUI components */
    std::unique_ptr<PhantomAmplifierComponent> m_phantomAmplifier;
    std::unique_ptr<PhantomOscillatorComponent> m_phantomOscillators;
    std::unique_ptr<PhantomPhasorComponent> m_phantomPhasors;
    std::unique_ptr<PhantomMixerComponent> m_phantomMixer;
    std::unique_ptr<PhantomFilterComponent> m_phantomFilter;
    std::unique_ptr<PhantomLFOComponent> m_phantomLFOs;
    std::unique_ptr<PhantomEnvelopeComponent> m_phantomEnvelopes;

    Label m_presetLabel;
    TextButton m_presetButton;
    TextButton m_presetLeftButton;
    TextButton m_presetRightButton;
};

#endif
