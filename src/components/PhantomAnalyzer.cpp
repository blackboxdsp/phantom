/*
  ==============================================================================

    PhantomAnalyzer.cpp
    Created: 12 Apr 2021 16:27:57
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomAnalyzer.h"

#include "../utils/PhantomUtils.h"

PhantomAnalyzerComponent::PhantomAnalyzerComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : IComponent(plf, vts), m_forwardFFT(FFT_ORDER), m_window(FFT_SIZE, dsp::WindowingFunction<float>::hann)
{
    init();
}

void PhantomAnalyzerComponent::init()
{
    zeromem(m_outputData, sizeof(m_outputData));
    startTimerHz(30);
}

PhantomAnalyzerComponent::~PhantomAnalyzerComponent()
{
    stopTimer();
}

void PhantomAnalyzerComponent::paint(Graphics& graphics)
{
    const float width = (float) getWidth();
    const float height = (float) getHeight();

    graphics.setColour(Colours::transparentBlack);
    graphics.fillAll();

    Range<float> maxRange = FloatVectorOperations::findMinAndMax(m_outputData, OUTPUT_SIZE);
    const float scale = 1.0f / jmax((float) FFT_SIZE, maxRange.getEnd());

    graphics.setColour(Consts::_FILL_END_COLOUR);
    for(int i = 0; i < OUTPUT_SIZE; i++) 
    {
        float x = std::log10f(1.0f + 39.0f * ((i + 1.0f) / OUTPUT_SIZE)) / std::log10f(40.0f) * width;

        float magnitude = m_outputData[i] * scale;
        float decibels = Decibels::gainToDecibels(magnitude);
        float y = jmap(decibels, -90.0f, -15.0f, height, 0.0f);

        graphics.drawVerticalLine((int) x, (int) y, height);
    }
}

void PhantomAnalyzerComponent::resized()
{

}

void PhantomAnalyzerComponent::timerCallback()
{
    if(m_isNextFFTBlockReady)
    {
        m_window.multiplyWithWindowingTable(m_FFTData, FFT_SIZE);
        m_forwardFFT.performFrequencyOnlyForwardTransform(m_FFTData);

        FloatVectorOperations::max(m_outputData, m_outputData, m_FFTData, OUTPUT_SIZE);

        m_isNextFFTBlockReady = false;
    }

    for(int i = 0; i < OUTPUT_SIZE; i++)
        m_outputData[i] *= 0.75f;

    repaint();
}

void PhantomAnalyzerComponent::pushBuffer(AudioSampleBuffer& buffer) noexcept
{
    if(buffer.getNumChannels() > 0)
    {
        const float* channelData = buffer.getReadPointer(0);

        for(int i = 0; i < buffer.getNumSamples(); i++)
            pushNextSample(channelData[i]);
    }
}

inline void PhantomAnalyzerComponent::pushNextSample(float sample) noexcept
{
    if(m_FFTQueueIndex == FFT_SIZE)
    {
        if(!m_isNextFFTBlockReady)
        {
            zeromem(m_FFTData, sizeof(m_FFTData));
            memcpy(m_FFTData, m_FFTQueue, sizeof(m_FFTQueue));

            m_isNextFFTBlockReady = true;
        }

        m_FFTQueueIndex = 0;
    }

    m_FFTQueue[m_FFTQueueIndex++] = sample;
}
