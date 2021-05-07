/*
  ==============================================================================

    PhantomPhasor.h
    Created: 06 May 2021 11:48:26
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_PHASOR_COMPONENT_H
#define _PHANTOM_PHASOR_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component class for the synth phasors.
 */
class PhantomPhasorComponent : public IComponent
{
public:
    PhantomPhasorComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts);
    ~PhantomPhasorComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomPhasorComponent)

    std::unique_ptr<Slider> m_phasor01ShapeSlider;
    std::unique_ptr<SliderAttachment> m_phasor01ShapeSliderAttachment;
    std::unique_ptr<Slider> m_phasor01EgIntSlider;
    std::unique_ptr<SliderAttachment> m_phasor01EgIntSliderAttachment;
    std::unique_ptr<Slider> m_phasor01LfoIntSlider;
    std::unique_ptr<SliderAttachment> m_phasor01LfoIntSliderAttachment;

    std::unique_ptr<Slider> m_phasor02ShapeSlider;
    std::unique_ptr<SliderAttachment> m_phasor02ShapeSliderAttachment;
    std::unique_ptr<Slider> m_phasor02EgIntSlider;
    std::unique_ptr<SliderAttachment> m_phasor02EgIntSliderAttachment;
    std::unique_ptr<Slider> m_phasor02LfoIntSlider;
    std::unique_ptr<SliderAttachment> m_phasor02LfoIntSliderAttachment;
};

#endif