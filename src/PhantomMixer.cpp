/*
  ==============================================================================

    PhantomAmplifier.h
    Created: 05 Apr 2021 14:11:33
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomMixer.h"

//==============================================================================
PhantomMixer::PhantomMixer(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    
}

PhantomMixer::~PhantomMixer()
{

}
