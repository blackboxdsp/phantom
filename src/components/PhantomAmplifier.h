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

/**
 * The GUI component class for the synth amplifier.
 */
class PhantomAmplifierComponent : public IComponent
{
public:
    PhantomAmplifierComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts);
    ~PhantomAmplifierComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAmplifierComponent)

    std::unique_ptr<Slider> m_levelSlider;
    std::unique_ptr<SliderAttachment> m_levelSliderAttachment;
};

#endif
