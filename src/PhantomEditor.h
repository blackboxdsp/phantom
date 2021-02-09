/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class PhantomAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor&, AudioProcessorValueTreeState&);
    ~PhantomAudioProcessorEditor() override;

    //==========================================================================
    void paint(Graphics&) override;
    void resized() override;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)

    //==========================================================================
    void reset();
    
    //==========================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhantomAudioProcessor& m_audioProcessor;

    AudioProcessorValueTreeState& m_parameters;

    //==========================================================================
    TextButton m_initButton;
    Label m_initLabel;

    Label m_oscLabel;
    Slider m_oscRangeSlider;
    Label m_oscRangeLabel;
    std::unique_ptr<SliderAttachment> m_oscRangeSliderAttachment;
    Slider m_oscCoarseTuneSlider;
    Label m_oscCoarseTuneLabel;
    std::unique_ptr<SliderAttachment> m_oscCoarseTuneSliderAttachment;
    Slider m_oscFineTuneSlider;
    Label m_oscFineTuneLabel;
    std::unique_ptr<SliderAttachment> m_oscFineTuneSliderAttachment;
    Slider m_oscModDepthSlider;
    Label m_oscModDepthLabel;
    std::unique_ptr<SliderAttachment> m_oscModDepthSliderAttachment;
    Slider m_oscModModeSlider;
    Label m_oscModModeLabel;
    std::unique_ptr<SliderAttachment> m_oscModModeSliderAttachment;
    Slider m_oscShapeIntSlider;
    Label m_oscShapeIntLabel;
    std::unique_ptr<SliderAttachment> m_oscShapeIntSliderAttachment;

    Label m_phasorLabel;
    Slider m_phasorShapeSlider;
    Label m_phasorShapeLabel;
    std::unique_ptr<SliderAttachment> m_phasorShapeSliderAttachment;
    Slider m_phasorEgIntSlider;
    Label m_phasorEgIntLabel;
    std::unique_ptr<SliderAttachment> m_phasorEgIntSliderAttachment;
    Slider m_phasorLfoIntSlider;
    Label m_phasorLfoIntLabel;
    std::unique_ptr<SliderAttachment> m_phasorLfoIntSliderAttachment;

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
    Slider m_filterEgModDepthSlider;
    Label m_filterEgModDepthLabel;
    std::unique_ptr<SliderAttachment> m_filterEgModDepthSliderAttachment;
    Slider m_filterLfoModDepthSlider;
    Label m_filterLfoModDepthLabel;
    std::unique_ptr<SliderAttachment> m_filterLfoModDepthSliderAttachment;

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
    Label m_filterEgAtkLabel;
    std::unique_ptr<SliderAttachment> m_filterEgAtkSliderAttachment;
    Slider m_filterEgDecSlider;
    Label m_filterEgDecLabel;
    std::unique_ptr<SliderAttachment> m_filterEgDecSliderAttachment;
    Slider m_filterEgSusSlider;
    Label m_filterEgSusLabel;
    std::unique_ptr<SliderAttachment> m_filterEgSusSliderAttachment;
    Slider m_filterEgRelSlider;
    Label m_filterEgRelLabel;
    std::unique_ptr<SliderAttachment> m_filterEgRelSliderAttachment;

    Label m_modEgLabel;
    Slider m_modEgAtkSlider;
    Label m_modEgAtkLabel;
    std::unique_ptr<SliderAttachment> m_modEgAtkSliderAttachment;
    Slider m_modEgDecSlider;
    Label m_modEgDecLabel;
    std::unique_ptr<SliderAttachment> m_modEgDecSliderAttachment;
    Slider m_modEgSusSlider;
    Label m_modEgSusLabel;
    std::unique_ptr<SliderAttachment> m_modEgSusSliderAttachment;
    Slider m_modEgRelSlider;
    Label m_modEgRelLabel;
    std::unique_ptr<SliderAttachment> m_modEgRelSliderAttachment;

    Label m_lfoLabel;
    Slider m_lfoRateSlider;
    Label m_lfoRateLabel;
    std::unique_ptr<SliderAttachment> m_lfoRateSliderAttachment;
    Slider m_lfoShapeSlider;
    Label m_lfoShapeLabel;
    std::unique_ptr<SliderAttachment> m_lfoShapeSliderAttachment;

    Label m_ampLabel;
    Slider m_levelSlider;
    Label m_levelLabel;
    std::unique_ptr<SliderAttachment> m_levelSliderAttachment; 
};
