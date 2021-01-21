/*
  ==============================================================================

    PhantomSynth.cpp
    Created: 21 Jan 2021 10:45:00am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomSynth.h"

#include "PhantomSound.h"
#include "PhantomVoice.h"

//==========================================================================
PhantomSynth::PhantomSynth(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    clear();
    init();
}

PhantomSynth::~PhantomSynth()
{
    clear();
}

//==============================================================================
void PhantomSynth::init()
{
    addVoices();
    addSounds();
}

void PhantomSynth::clear()
{
    clearSounds();
    clearVoices();
}

//==============================================================================
void PhantomSynth::addVoices()
{
    for(int i = 0; i < k_numVoices; i++)
    {
        PhantomVoice* voice = new PhantomVoice(m_parameters);
        addVoice(voice);
    }
}

void PhantomSynth::addSounds()
{
    PhantomSound* sound = new PhantomSound();
    addSound(sound);
}
