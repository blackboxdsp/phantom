/*
  ==============================================================================

    IComponent.h
    Created: 05 May 2021 22:08:46
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "JuceHeader.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

/**
 * This class contains the methods and common attributes of component classes, which hold 
 * things like visual elements or parameter sliders.
 */
class IComponent : public Component
{
public:
    IComponent() : m_parameters() { };
    IComponent(AudioProcessorValueTreeState& vts) : m_parameters(&vts) { };
    
    ~IComponent() { m_parameters.release(); };

    /**
     * For initializing the component (i.e. configuring sliders, clearing data)
     */
    virtual void init() = 0;

    /**
     * For updating the component's visual layout, usually called by its parent.
     * @param bounds The reference to the `Rectangle` object to use in sectioning this component.
     */
    void update(Rectangle<int>& bounds) { setBounds(bounds); };
    
    /**
     * For updating the component's visual layout, usually called by its parent.
     * @param margin The margin to use in spacing the inner components of this component.
     * @param knobWidth The width to use for an individual slider.
     * @param bounds The reference to the `Rectangle` object to use in sectioning this component.
     */
    void update(const int margin, const int knobWidth, Rectangle<int>& bounds) { m_margin = margin; m_knobWidth = knobWidth; setBounds(bounds); };

    /**
     * NOTE: Each individual component must override and define its own `paint(Graphics& g)` and `resized()`
     * methods in order to be drawn to the screen.
     */

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IComponent)

    std::unique_ptr<AudioProcessorValueTreeState> m_parameters;

    /** The width value for general text boxes. */
    const unsigned int m_textBoxWidth = 80;

    /** The height value for general text boxes. */
    const unsigned int m_textBoxHeight = 20;

    /** The margin to use in spacing the inner components of this component. */
    unsigned int m_margin = -1;

    /** The knob width to use in spacing the sliders of this component. */
    unsigned int m_knobWidth = -1;
};

#endif
