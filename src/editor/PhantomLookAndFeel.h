/*
  ==============================================================================

    PhantomLookAndFeel.h
    Created: 05 May 2021 16:15:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_LOOK_AND_FEEL_H
#define _PHANTOM_LOOK_AND_FEEL_H

#include "JuceHeader.h"

#include "../utils/PhantomUtils.h"

class PhantomLookAndFeel : public LookAndFeel_V4
{
public:
    PhantomLookAndFeel() { };
    ~PhantomLookAndFeel() { };

    void drawPopupMenuBackground(
        Graphics& g,
        int width,
        int height
    ) override;

    void drawPopupMenuItem(
        Graphics& g,
        const Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
        const String& text,
        const String& shortcutKeyText,
        const Drawable* icon,
        const Colour* textColour
    ) override;

    void drawPopupMenuSectionHeader(
        Graphics& g,
        const Rectangle<int>& area,
        const String& sectionName
    ) override;

    void drawRotarySlider(
        Graphics& g,
        int x, int y,
        int width, int height,
        float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
        Slider& s
    ) override;

    void drawToggleButton(
        Graphics& g, ToggleButton& b, 
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown
    ) override;

    void drawCornerResizer(
        Graphics& g,
        int width, int height,
        bool isMouseOver, bool isMouseDragging
    ) override;

    Font getPopupMenuFont() override;
    Font getTextButtonFont(TextButton& tb, int buttonHeight) override;
    
    /**
     * Sets the font size (px) of the look and feel configuration.
     * @param windowWidth The window width (px) of the plugin, used for calculating the font size from a ratio.
     */
    void setFontSize(int windowWidth);
    
    /**
     * Sets the stoke width size (px) of the look and feel configuration.
     * @param windowWidth The window width (px) of the plugin, used for calculating the stroke width from a ratio.
     */
    void setStrokeWidth(int windowWidth);

    /**
     * NOTE: Every hard-coded value and ratio here is calculated from the corresponding area
     * on the design file. For example, the oscillator section is 2,790px in width, 
     * which when applied in ratio to the width reduces down to 93 / 128. Some of these values have been
     * slightly modified from the originally calculated value.
     */

    static constexpr float _MARGIN_PER_WIDTH = 3.0f / 256.0f;
    static constexpr float _SECTION_PER_HEIGHT = 7.0f / 32.0f;
    static constexpr float _SLIDER_PER_WIDTH = 1.0f / 20.0f;
    static constexpr float _LARGE_SLIDER_PER_WIDTH = 7.0f / 238.0f;
    static constexpr float _BUTTON_PER_HEIGHT = 1.0f / 36.0f;
    static constexpr float _FONT_PER_WIDTH = 1.0f / 105.0f;
    static constexpr float _STROKE_PER_WIDTH = 3.0f / 6400.0f;

private:
    /**
     * Computes the appopriate readout values for sliders, taking into account some important questions like number polarity.
     * @param slider The slider value to compute the readout for.
     * @param nameTokens The StringArray of tokens parsed from the slider's name beforehand.
     * @returns The complete readout string for the slider including the appropriate suffix.
     */
    String getSliderReadout(Slider& slider, StringArray& nameTokens);

    /**
     * Retrieves the font at the default font size.
     * @returns The Montserrat font at the default font size.
     */
    Font getFont() const;
    
    /**
     * Retrieves the default font at the given size.
     * @param fontSize The size (px) to set the font to.
     * @returns The Montserrat font at the given size (px).
     */
    Font getFont(float fontSize) const;

    /**
     * Calculates padding for things like a PopupMenu.
     * @returns The padding amount (px) calculated from the font size.
     */
    float getPadding();

    /** The font size (px) to use for text and layouts. */
    float m_fontSize = 12.0f;

    /** The stroke width (px) to use in drawing sliders and other visual components. */ 
    float m_strokeWidth = 1.8f;
};

#endif
