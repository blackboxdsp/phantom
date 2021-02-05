/*
  ==============================================================================

    PhantomLFO.h
    Created: 27 Jan 2021 18:51:41
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "JuceHeader.h"

class PhantomLFO 
{
public:
    //==========================================================================
    PhantomLFO(AudioProcessorValueTreeState&);
    ~PhantomLFO();

    //==========================================================================
    void update(float sampleRate) noexcept;

    //==========================================================================
    float evaluate() noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomLFO)

    //==========================================================================
    void initParameters();
    void resetWavetable() noexcept;

    void updatePhaseDelta() noexcept;

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_rate;
    std::atomic<float>* p_shape;

    float m_previousShape;
    //==========================================================================
    Array<float> m_wavetable;

    float m_phase = 0.0f;
    float m_phaseDelta = 0.0f;

    float m_sampleRate;
    float m_sampleValue = 0.0f;

    int m_count = 0;
};