/*
  ==============================================================================

    PhantomFilter.cpp
    Created: 23 Jan 2021 21:22:03
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomFilter.h"

//==============================================================================
PhantomFilter::PhantomFilter(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    initFilter();
}

void PhantomFilter::initFilter()
{
    m_filter = new dsp::LadderFilter<float>();
}
