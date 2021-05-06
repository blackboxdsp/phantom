/*
  ==============================================================================

    PhantomAmplifier.h
    Created: 05 May 2021 18:22:43
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_AMPLIFIER_COMPONENT_H
#define _PHANTOM_AMPLIFIER_COMPONENT_H

#include "../interfaces/IComponent.h"
#include "../utils/PhantomUtils.h"

/**
 * This component class contains the parameter sliders for the amplifier section.
 */
class PhantomAmplifierComponent : public IComponent
{
public:
    PhantomAmplifierComponent(AudioProcessorValueTreeState& vts);
    ~PhantomAmplifierComponent();

    void init() override;
    void update(const int margin, const int knobWidth, Rectangle<int>& bounds) override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAmplifierComponent)

    std::unique_ptr<Slider> m_levelSlider;
    std::unique_ptr<Label> m_levelLabel;
    std::unique_ptr<SliderAttachment> m_levelSliderAttachment;
};

#endif
