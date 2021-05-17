/*
  ==============================================================================

    PhnatomOscillator.h
    Created: 06 May 2021 08:20:43
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_OSCILLATOR_COMPONENT_H
#define _PHANTOM_OSCILLATOR_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component class for the synth oscillators.
 */
class PhantomOscillatorComponent : public IComponent
{
public:
    PhantomOscillatorComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts);
    ~PhantomOscillatorComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscillatorComponent)

    std::unique_ptr<Slider> m_oscSyncSlider;
    std::unique_ptr<SliderAttachment> m_oscSyncSliderAttachment;

    std::unique_ptr<ToggleButton> m_oscSyncButton;
    std::unique_ptr<ButtonAttachment> m_oscSyncButtonAttachment;

    std::unique_ptr<Slider> m_osc01RangeSlider;
    std::unique_ptr<SliderAttachment> m_osc01RangeSliderAttachment;
    std::unique_ptr<Slider> m_osc01CoarseTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc01CoarseTuneSliderAttachment;
    std::unique_ptr<Slider> m_osc01FineTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc01FineTuneSliderAttachment;
    std::unique_ptr<Slider> m_osc01ShapeIntSlider;
    std::unique_ptr<SliderAttachment> m_osc01ShapeIntSliderAttachment;
    std::unique_ptr<Slider> m_osc01ModDepthSlider;
    std::unique_ptr<SliderAttachment> m_osc01ModDepthSliderAttachment;
    std::unique_ptr<Slider> m_osc01ModSourceSlider;
    std::unique_ptr<SliderAttachment> m_osc01ModSourceSliderAttachment;
    
    std::unique_ptr<Slider> m_osc02RangeSlider;
    std::unique_ptr<SliderAttachment> m_osc02RangeSliderAttachment;
    std::unique_ptr<Slider> m_osc02CoarseTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc02ModSourceSliderAttachment;
    std::unique_ptr<Slider> m_osc02ShapeIntSlider;
    std::unique_ptr<SliderAttachment> m_osc02ShapeIntSliderAttachment;
    std::unique_ptr<SliderAttachment> m_osc02CoarseTuneSliderAttachment;
    std::unique_ptr<Slider> m_osc02FineTuneSlider;
    std::unique_ptr<SliderAttachment> m_osc02FineTuneSliderAttachment;
    std::unique_ptr<Slider> m_osc02ModDepthSlider;
    std::unique_ptr<SliderAttachment> m_osc02ModDepthSliderAttachment;
    std::unique_ptr<Slider> m_osc02ModSourceSlider;
};

#endif