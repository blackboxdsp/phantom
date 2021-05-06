/*
  ==============================================================================

    PhantomEnvelope.h
    Created: 06 May 2021 14:36:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_ENVELOPE_COMPONENT_H
#define _PHANTOM_ENVELOPE_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component for the synth's envelope generators.
 */
class PhantomEnvelopeComponent : public IComponent
{
public:
    PhantomEnvelopeComponent(AudioProcessorValueTreeState& vts);
    ~PhantomEnvelopeComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomEnvelopeComponent)

    void initAmpEnvelope();
    void initPhasorEnvelope();
    void initFilterEnvelope();
    void initModEnvelope();

    std::unique_ptr<Slider> m_ampEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_ampEgAtkSliderAttachment;
    std::unique_ptr<Slider> m_ampEgDecSlider;
    std::unique_ptr<SliderAttachment> m_ampEgDecSliderAttachment;
    std::unique_ptr<Slider> m_ampEgSusSlider;
    std::unique_ptr<SliderAttachment> m_ampEgSusSliderAttachment;
    std::unique_ptr<Slider> m_ampEgRelSlider;
    std::unique_ptr<SliderAttachment> m_ampEgRelSliderAttachment;

    std::unique_ptr<Slider> m_phasorEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgAtkSliderAttachment;
    std::unique_ptr<Slider> m_phasorEgDecSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgDecSliderAttachment;
    std::unique_ptr<Slider> m_phasorEgSusSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgSusSliderAttachment;
    std::unique_ptr<Slider> m_phasorEgRelSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgRelSliderAttachment;

    std::unique_ptr<Slider> m_filterEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_filterEgAtkSliderAttachment;
    std::unique_ptr<Slider> m_filterEgDecSlider;
    std::unique_ptr<SliderAttachment> m_filterEgDecSliderAttachment;
    std::unique_ptr<Slider> m_filterEgSusSlider;
    std::unique_ptr<SliderAttachment> m_filterEgSusSliderAttachment;
    std::unique_ptr<Slider> m_filterEgRelSlider;
    std::unique_ptr<SliderAttachment> m_filterEgRelSliderAttachment;

    std::unique_ptr<Slider> m_modEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_modEgAtkSliderAttachment;
    std::unique_ptr<Slider> m_modEgDecSlider;
    std::unique_ptr<SliderAttachment> m_modEgDecSliderAttachment;
    std::unique_ptr<Slider> m_modEgSusSlider;
    std::unique_ptr<SliderAttachment> m_modEgSusSliderAttachment;
    std::unique_ptr<Slider> m_modEgRelSlider;
    std::unique_ptr<SliderAttachment> m_modEgRelSliderAttachment;
};

#endif
