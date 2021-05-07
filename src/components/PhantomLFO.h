/*
  ==============================================================================

    PhantomLFO.h
    Created: 06 May 2021 13:26:58
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_LFO_COMPONENT_H
#define _PHANTOM_LFO_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component class for the synths low-frequency oscillator (LFO).
 */
class PhantomLFOComponent : public IComponent
{
public:
    PhantomLFOComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts);
    ~PhantomLFOComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomLFOComponent)

    std::unique_ptr<Slider> m_lfo01RateSlider;
    std::unique_ptr<SliderAttachment> m_lfo01RateSliderAttachment;
    std::unique_ptr<Slider> m_lfo01ShapeSlider;
    std::unique_ptr<SliderAttachment> m_lfo01ShapeSliderAttachment;
    
    std::unique_ptr<Slider> m_lfo02RateSlider;
    std::unique_ptr<SliderAttachment> m_lfo02RateSliderAttachment;
    std::unique_ptr<Slider> m_lfo02ShapeSlider;
    std::unique_ptr<SliderAttachment> m_lfo02ShapeSliderAttachment;
};

#endif
