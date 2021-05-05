/*
  ==============================================================================

    PhantomLookAndFeel.h
    Created: 05 May 2021 16:15:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLookAndFeel.h"

#include "../utils/PhantomData.h"

const Font& PhantomLookAndFeel::getSliderReadoutFont()
{
    static Font readout(Font(Typeface::createSystemTypefaceFor(
        PhantomData::montserrat_ttf, PhantomData::montserrat_ttfSize
    )));
    readout.setHeight(k_fontSize);

    return readout;
}
