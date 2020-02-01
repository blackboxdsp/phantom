/*
  ==============================================================================

    PhantomSound.h
    Created: 1 Feb 2020 8:35:14am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class PhantomSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /* midiNoteNumber */)
    {
        return true;
    }
    bool appliesToChannel(int /* midiChannel */)
    {
        return true;
    }
};