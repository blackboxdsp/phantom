/*
  ==============================================================================

    PhantomAmplifier.h
    Created: 05 Apr 2021 14:11:33
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "JuceHeader.h"

class PhantomMixer
{
public:
    //==========================================================================
    PhantomMixer(AudioProcessorValueTreeState&);
    ~PhantomMixer();

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomMixer)

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;
};
