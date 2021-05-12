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
#include "../utils/PhantomData.h"

/**
 * The GUI component for the synth's envelope generators.
 */
class PhantomEnvelopeComponent : public IComponent
{
public:
    PhantomEnvelopeComponent(EnvelopeType et, PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts);
    ~PhantomEnvelopeComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomEnvelopeComponent)

    void prepareForEgSlider(const bool removeOtherHalf, const int expandBy, Rectangle <int>& bounds);

    EnvelopeType m_type;

    std::unique_ptr<Slider> m_egAtkSlider;
    std::unique_ptr<SliderAttachment> m_egAtkSliderAttachment;
    std::unique_ptr<Slider> m_egDecSlider;
    std::unique_ptr<SliderAttachment> m_egDecSliderAttachment;
    std::unique_ptr<Slider> m_egSusSlider;
    std::unique_ptr<SliderAttachment> m_egSusSliderAttachment;
    std::unique_ptr<Slider> m_egRelSlider;
    std::unique_ptr<SliderAttachment> m_egRelSliderAttachment;
};

#endif
