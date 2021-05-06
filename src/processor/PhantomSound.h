/*
  ==============================================================================

    PhantomSound.h
    Created: 21 Jan 2021 10:49:28am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_SOUND_H
#define _PHANTOM_SOUND_H

#include "JuceHeader.h"

/**
 * The sound class used in the `PhantomSynthesizer` class.
 */
class PhantomSound : public SynthesiserSound
{
public:
    /**
     * Overridden JUCE method for MIDI note number.
     */
    bool appliesToNote(int midiNoteNumber) override;

    /**
     * Overridden JUCE method for MIDI channel.
     */
    bool appliesToChannel(int midiChannelNumber) override;
};

#endif
