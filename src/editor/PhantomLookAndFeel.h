/*
  ==============================================================================

    PhantomLookAndFeel.h
    Created: 05 May 2021 16:15:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "../utils/PhantomUtils.h"

class PhantomLookAndFeel : public LookAndFeel_V4
{
public:
    PhantomLookAndFeel()    { };
    ~PhantomLookAndFeel()   { };

private:
    const float k_strokeWidth = 1.8f;

    const float k_fontSize = 9.0f;
    const Font& getSliderReadoutFont();
};
