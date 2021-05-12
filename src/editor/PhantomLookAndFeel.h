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

private:
    const float k_strokeWidth = 1.8f;

    const float k_fontSize = 9.0f;
    const Font& getSliderReadoutFont();
};

#endif
