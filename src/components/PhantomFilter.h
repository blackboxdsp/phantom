/*
  ==============================================================================

    PhantomFilter.h
    Created: 06 May 2021 13:07:06
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_FILTER_COMPONENT_H
#define _PHANTOM_FILTER_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component component class for the synth's filter.
 */
class PhantomFilterComponent : public IComponent
{
public:
    PhantomFilterComponent(AudioProcessorValueTreeState& vts);
    ~PhantomFilterComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

private: 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomFilterComponent)

    std::unique_ptr<Slider> m_filterCutoffSlider;
    std::unique_ptr<SliderAttachment> m_filterCutoffSliderAttachment;

    std::unique_ptr<Slider> m_filterResoSlider;
    std::unique_ptr<SliderAttachment> m_filterResoSliderAttachment;

    std::unique_ptr<Slider> m_filterDriveSlider;
    std::unique_ptr<SliderAttachment> m_filterDriveSliderAttachment;

    std::unique_ptr<Slider> m_filterModeSlider;
    std::unique_ptr<SliderAttachment> m_filterModeSliderAttachment;

    std::unique_ptr<Slider> m_filterEgModDepthSlider;
    std::unique_ptr<SliderAttachment> m_filterEgModDepthSliderAttachment;

    std::unique_ptr<Slider> m_filterLfoModDepthSlider;
    std::unique_ptr<SliderAttachment> m_filterLfoModDepthSliderAttachment;
};

#endif
