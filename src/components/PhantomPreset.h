/*
  ==============================================================================

    PhantomPreset.h
    Created: 06 May 2021 15:54:04
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_PRESET_COMPONENT_H
#define _PHANTOM_PRESET_COMPONENT_H

#include "../interfaces/IComponent.h"
#include "../processor/PhantomPresetManager.h"

class PhantomPresetComponent : public IComponent
{
public:
    PhantomPresetComponent(PhantomLookAndFeel& plf, PhantomPresetManager& pm, AudioProcessorValueTreeState& vts);
    ~PhantomPresetComponent();

    void init() override;
    void reset() override;

    void paint(Graphics& g) override;
    void resized() override;

    /**
     * Adds presets from presets folder to popup menu.
     * @param menu The reference to the menu to add the presets to.
     */
    void addPresetsToMenu(PopupMenu &menu);

    /** The reference to the preset manager object. */
    PhantomPresetManager& m_presetManager;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomPresetComponent)

    /** The alpha value to use for the colors of buttons which are idle. */
    const float k_idleButtonAlpha = 0.0f;

    /** The alpha value to use for the colors of buttons which the mouse is hovered over. */
    const float k_hoverButtonAlpha = 0.25f;

    /** The button object triggering the preset menu. */
    std::unique_ptr<TextButton> m_presetButton;

    /** 
     * NOTE: The following buttons are for directionally scrolling through presets.
     */

    std::unique_ptr<TextButton> m_presetLeftButton;
    std::unique_ptr<TextButton> m_presetRightButton;
};

#endif
