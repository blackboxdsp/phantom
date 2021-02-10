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

    Label m_osc01Label;
    Slider m_osc01RangeSlider;
    Label m_osc01RangeLabel;
    std::unique_ptr<SliderAttachment> m_osc01RangeSliderAttachment;
    Slider m_osc01CoarseTuneSlider;
    Label m_osc01CoarseTuneLabel;
    std::unique_ptr<SliderAttachment> m_osc01CoarseTuneSliderAttachment;
    Slider m_osc01FineTuneSlider;
    Label m_osc01FineTuneLabel;
    std::unique_ptr<SliderAttachment> m_osc01FineTuneSliderAttachment;
    Slider m_osc01ModDepthSlider;
    Label m_osc01ModDepthLabel;
    std::unique_ptr<SliderAttachment> m_osc01ModDepthSliderAttachment;
    Slider m_osc01ModModeSlider;
    Label m_osc01ModModeLabel;
    std::unique_ptr<SliderAttachment> m_osc01ModModeSliderAttachment;
    Slider m_osc01ShapeIntSlider;
    Label m_osc01ShapeIntLabel;
    std::unique_ptr<SliderAttachment> m_osc01ShapeIntSliderAttachment;

    Label m_osc02Label;
    Slider m_osc02RangeSlider;
    std::unique_ptr<SliderAttachment> m_osc02RangeSliderAttachment;
    Slider m_osc02CoarseTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc02CoarseTuneSliderAttachment;
    Slider m_osc02FineTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc02FineTuneSliderAttachment;
    Slider m_osc02ModDepthSlider;
    std::unique_ptr<SliderAttachment> m_osc02ModDepthSliderAttachment;
    Slider m_osc02ModModeSlider;
    std::unique_ptr<SliderAttachment> m_osc02ModModeSliderAttachment;
    Slider m_osc02ShapeIntSlider;
    std::unique_ptr<SliderAttachment> m_osc02ShapeIntSliderAttachment;

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
