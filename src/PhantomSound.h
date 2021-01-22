/*
  ==============================================================================

    PhantomSound.h
    Created: 21 Jan 2021 10:49:28am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomSound : public SynthesiserSound
{
public:
    //==========================================================================
    bool appliesToNote(int midiNoteNumber) override;
    bool appliesToChannel(int midiChannelNumber) override;
};
