/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomAnalyzer.h"
#include "PhantomOscilloscope.h"
#include "PhantomProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

/**
 * The editor component holding most of the code responsible for the
 * GUI (sliders, buttons, text, etc.).
 */
class PhantomAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor&, AudioProcessorValueTreeState&);
    ~PhantomAudioProcessorEditor() override;

    /**
     * Determines the appearance of the main plugin component.
     */
    void paint(Graphics&) override;

    /**
     * Determines the layout of the various GUI components for new 
     * window size.
     */
    void resized() override;

    /**
     * The unique pointer to the analyzer, used by the processor.
     */
    std::unique_ptr<PhantomAnalyzer> m_analyzer;

    /**
     * The unique pointer to the oscilloscope, used by the processor.
     */
    std::unique_ptr<PhantomOscilloscope> m_oscilloscope;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)

    /**
     * Initializes the variables for the GUI's layout.
     */
    void initLayoutVariables();

    /**
     * Initializes the GUI for the amplifier.
     */
    void initAmpGui();

    /**
     * Initializes the GUI for the oscillators.
     */
    void initOscillatorGui();

    /**
     * Initializes the GUI for the phasors.
     */
    void initPhasorGui();

    /**
     * Initializes the GUI for the mixer.
     */
    void initMixerGui();

    /**
     * Initializes the GUI for the filter.
     */
    void initFilterGui();

    /**
     * Initializes the GUI for the LFO.
     */
    void initLfoGui();

    /**
     * Initializes the GUI for the envelope generators.
     */
    void initEgGui();

    /**
     * Initializes the oscilloscope GUI component.
     */
    void initOscilloscope();

    /**
     * Initializes the analyzer GUI component.
     */
    void initAnalyzer();

    /**
     * Initializes the GUI for the preset menu.
     */
    void initPresetMenu();

    /**
     * Resets all of the sliders to their default values, useful for 
     * initializing new synth patches.
     */
    void reset();
    
    /**
     * This reference is provided as a quick way for your editor to
     * access the processor object that created it.
     */
    PhantomAudioProcessor& m_audioProcessor;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The width for a text box.
     */
    int textBoxWidth;

    /**
     * The height for a text box;
     */
    int textBoxHeight;

    //================
    // GUI COMPONENTS
    //================

    TextButton m_initButton;

    Slider m_levelSlider;
    Label m_levelLabel;
    std::unique_ptr<SliderAttachment> m_levelSliderAttachment; 

    Label m_oscLabel;
    Slider m_oscSyncSlider;
    Label m_oscSyncLabel;
    std::unique_ptr<SliderAttachment> m_oscSyncSliderAttachment;
    Slider m_osc01RangeSlider;
    Label m_osc01RangeLabel;
    std::unique_ptr<SliderAttachment> m_osc01RangeSliderAttachment;
    Slider m_osc01CoarseTuneSlider;
    Label m_osc01CoarseTuneLabel;
    std::unique_ptr<SliderAttachment> m_osc01CoarseTuneSliderAttachment;
    Slider m_osc01FineTuneSlider;
    Label m_osc01FineTuneLabel;
    std::unique_ptr<SliderAttachment> m_osc01FineTuneSliderAttachment;
    Slider m_osc01ShapeIntSlider;
    Label m_osc01ShapeIntLabel;
    std::unique_ptr<SliderAttachment> m_osc01ShapeIntSliderAttachment;
    Slider m_osc01ModDepthSlider;
    Label m_osc01ModDepthLabel;
    std::unique_ptr<SliderAttachment> m_osc01ModDepthSliderAttachment;
    Slider m_osc01ModSourceSlider;
    Label m_osc01ModSourceLabel;
    std::unique_ptr<SliderAttachment> m_osc01ModSourceSliderAttachment;
    Slider m_osc02RangeSlider;
    std::unique_ptr<SliderAttachment> m_osc02RangeSliderAttachment;
    Slider m_osc02CoarseTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc02ModSourceSliderAttachment;
    Slider m_osc02ShapeIntSlider;
    std::unique_ptr<SliderAttachment> m_osc02ShapeIntSliderAttachment;
    std::unique_ptr<SliderAttachment> m_osc02CoarseTuneSliderAttachment;
    Slider m_osc02FineTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc02FineTuneSliderAttachment;
    Slider m_osc02ModDepthSlider;
    std::unique_ptr<SliderAttachment> m_osc02ModDepthSliderAttachment;
    Slider m_osc02ModSourceSlider;

    Label m_phasorLabel;
    Slider m_phasor01ShapeSlider;
    Label m_phasor01ShapeLabel;
    std::unique_ptr<SliderAttachment> m_phasor01ShapeSliderAttachment;
    Slider m_phasor01EgIntSlider;
    Label m_phasor01EgIntLabel;
    std::unique_ptr<SliderAttachment> m_phasor01EgIntSliderAttachment;
    Slider m_phasor01LfoIntSlider;
    Label m_phasor01LfoIntLabel;
    std::unique_ptr<SliderAttachment> m_phasor01LfoIntSliderAttachment;
    Slider m_phasor02ShapeSlider;
    std::unique_ptr<SliderAttachment> m_phasor02ShapeSliderAttachment;
    Slider m_phasor02EgIntSlider;
    std::unique_ptr<SliderAttachment> m_phasor02EgIntSliderAttachment;
    Slider m_phasor02LfoIntSlider;
    std::unique_ptr<SliderAttachment> m_phasor02LfoIntSliderAttachment;

    Label m_mixerLabel;
    Slider m_mixerOscBalanceSlider;
    Label m_mixerOscBalanceLabel;
    std::unique_ptr<SliderAttachment> m_mixerOscBalanceSliderAttachment;
    Slider m_mixerAmpGainSlider;
    Label m_mixerAmpGainLabel;
    std::unique_ptr<SliderAttachment> m_mixerAmpGainSliderAttachment;
    Slider m_mixerRingModSlider;
    Label m_mixerRingModLabel;
    std::unique_ptr<SliderAttachment> m_mixerRingModSliderAttachment;
    Slider m_mixerNoiseSlider;
    Label m_mixerNoiseLabel;
    std::unique_ptr<SliderAttachment> m_mixerNoiseSliderAttachment;

    Label m_filterLabel;
    Slider m_filterCutoffSlider;
    Label m_filterCutoffLabel;
    std::unique_ptr<SliderAttachment> m_filterCutoffSliderAttachment;
    Slider m_filterResoSlider;
    Label m_filterResoLabel;
    std::unique_ptr<SliderAttachment> m_filterResoSliderAttachment;
    Slider m_filterDriveSlider;
    Label m_filterDriveLabel;
    std::unique_ptr<SliderAttachment> m_filterDriveSliderAttachment;
    Slider m_filterModeSlider;
    Label m_filterModeLabel;
    std::unique_ptr<SliderAttachment> m_filterModeSliderAttachment;
    Slider m_filterEgModDepthSlider;
    Label m_filterEgModDepthLabel;
    std::unique_ptr<SliderAttachment> m_filterEgModDepthSliderAttachment;
    Slider m_filterLfoModDepthSlider;
    Label m_filterLfoModDepthLabel;
    std::unique_ptr<SliderAttachment> m_filterLfoModDepthSliderAttachment;

    Label m_lfoLabel;
    Slider m_lfo01RateSlider;
    Label m_lfo01RateLabel;
    std::unique_ptr<SliderAttachment> m_lfo01RateSliderAttachment;
    Slider m_lfo01ShapeSlider;
    Label m_lfo01ShapeLabel;
    std::unique_ptr<SliderAttachment> m_lfo01ShapeSliderAttachment;
    Slider m_lfo02RateSlider;
    std::unique_ptr<SliderAttachment> m_lfo02RateSliderAttachment;
    Slider m_lfo02ShapeSlider;
    std::unique_ptr<SliderAttachment> m_lfo02ShapeSliderAttachment;

    Label m_ampEgLabel;
    Slider m_ampEgAtkSlider;
    Label m_ampEgAtkLabel;
    std::unique_ptr<SliderAttachment> m_ampEgAtkSliderAttachment;
    Slider m_ampEgDecSlider;
    Label m_ampEgDecLabel;
    std::unique_ptr<SliderAttachment> m_ampEgDecSliderAttachment;
    Slider m_ampEgSusSlider;
    Label m_ampEgSusLabel;
    std::unique_ptr<SliderAttachment> m_ampEgSusSliderAttachment;
    Slider m_ampEgRelSlider;
    Label m_ampEgRelLabel;
    std::unique_ptr<SliderAttachment> m_ampEgRelSliderAttachment;

    Label m_phasorEgLabel;
    Slider m_phasorEgAtkSlider;
    Label m_phasorEgAtkLabel;
    std::unique_ptr<SliderAttachment> m_phasorEgAtkSliderAttachment;
    Slider m_phasorEgDecSlider;
    Label m_phasorEgDecLabel;
    std::unique_ptr<SliderAttachment> m_phasorEgDecSliderAttachment;
    Slider m_phasorEgSusSlider;
    Label m_phasorEgSusLabel;
    std::unique_ptr<SliderAttachment> m_phasorEgSusSliderAttachment;
    Slider m_phasorEgRelSlider;
    Label m_phasorEgRelLabel;
    std::unique_ptr<SliderAttachment> m_phasorEgRelSliderAttachment;

    Label m_filterEgLabel;
    Slider m_filterEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_filterEgAtkSliderAttachment;
    Slider m_filterEgDecSlider;
    std::unique_ptr<SliderAttachment> m_filterEgDecSliderAttachment;
    Slider m_filterEgSusSlider;
    std::unique_ptr<SliderAttachment> m_filterEgSusSliderAttachment;
    Slider m_filterEgRelSlider;
    std::unique_ptr<SliderAttachment> m_filterEgRelSliderAttachment;

    Label m_modEgLabel;
    Slider m_modEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_modEgAtkSliderAttachment;
    Slider m_modEgDecSlider;
    std::unique_ptr<SliderAttachment> m_modEgDecSliderAttachment;
    Slider m_modEgSusSlider;
    std::unique_ptr<SliderAttachment> m_modEgSusSliderAttachment;
    Slider m_modEgRelSlider;
    std::unique_ptr<SliderAttachment> m_modEgRelSliderAttachment;

    Label m_presetsLabel;
};
