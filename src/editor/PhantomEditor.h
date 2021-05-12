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
#include "../components/PhantomPreset.h"
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

    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

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
     * Resets all of the sliders to their default values, useful for 
     * initializing new synth patches.
     */
    void reset();

    /**
     * The unique pointer to the analyzer, used by the processor.
     */
    std::unique_ptr<PhantomAnalyzerComponent> m_phantomAnalyzer;

    /**
     * The unique pointer to the oscilloscope, used by the processor.
     */
    std::unique_ptr<PhantomOscilloscopeComponent> m_phantomOscilloscope;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)

    /** Initializes the editor component. */
    void init();

    /**
     * This reference is provided as a quick way for your editor to
     * access the processor object that created it.
     */
    PhantomAudioProcessor &m_processor;

    /** The reference to the value tree state useful in retrieving or 
     * storing parameter information.
     */
    AudioProcessorValueTreeState &m_parameters;

    /** The custom look and feel for the plugin. */
    PhantomLookAndFeel m_lookAndFeel;

    /** GUI components */
    std::unique_ptr<PhantomAmplifierComponent> m_phantomAmplifier;
    std::unique_ptr<PhantomOscillatorComponent> m_phantomOscillators;
    std::unique_ptr<PhantomPhasorComponent> m_phantomPhasors;
    std::unique_ptr<PhantomMixerComponent> m_phantomMixer;
    std::unique_ptr<PhantomFilterComponent> m_phantomFilter;

    std::unique_ptr<PhantomLFOComponent> m_phantomLFOs;
    
    std::unique_ptr<PhantomEnvelopeComponent> m_phantomAmpEg;
    std::unique_ptr<PhantomEnvelopeComponent> m_phantomPhasorEg;
    std::unique_ptr<PhantomEnvelopeComponent> m_phantomFilterEg;
    std::unique_ptr<PhantomEnvelopeComponent> m_phantomModEg;

    std::unique_ptr<PhantomPresetComponent> m_phantomPreset;
};

#endif
