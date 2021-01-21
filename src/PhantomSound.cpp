/*
  ==============================================================================

    PhantomSound.cpp
    Created: 21 Jan 2021 10:49:28am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomSound.h"

//==========================================================================
bool PhantomSound::appliesToNote(int midiNoteNumber) 
{
    return true;
}

bool PhantomSound::appliesToChannel(int midiChannelNumber) 
{
    return true;
}
