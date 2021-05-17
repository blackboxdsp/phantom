/*
  ==============================================================================

    PhantomMixer.h
    Created: 06 May 2021 12:19:23
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_MIXER_COMPONENT_H
#define _PHANTOM_MIXER_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component class for the synth mixer, which sums the oscillators.
 */
class PhantomMixerComponent : public IComponent
{
public:
    PhantomMixerComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts);
    ~PhantomMixerComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomMixerComponent)

    std::unique_ptr<Slider> m_mixerOscBalanceSlider;
    std::unique_ptr<SliderAttachment> m_mixerOscBalanceSliderAttachment;
    
    std::unique_ptr<Slider> m_mixerAmpGainSlider;
    std::unique_ptr<SliderAttachment> m_mixerAmpGainSliderAttachment;
    
    std::unique_ptr<Slider> m_mixerRingModSlider;
    std::unique_ptr<SliderAttachment> m_mixerRingModSliderAttachment;
    
    std::unique_ptr<Slider> m_mixerNoiseSlider;
    std::unique_ptr<SliderAttachment> m_mixerNoiseSliderAttachment;
};

#endif
