/*
  ==============================================================================

    PhantomOscilloscope.cpp
    Created: 12 Apr 2021 17:56:42
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscilloscope.h"

#include "../effects/PhantomWaveshaper.h"
#include "../utils/PhantomUtils.h"

PhantomOscilloscopeComponent::PhantomOscilloscopeComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : IComponent(plf, vts)
{
    init();
}

PhantomOscilloscopeComponent::~PhantomOscilloscopeComponent()
{
    stopTimer();

    m_buffer = nullptr;
}

void PhantomOscilloscopeComponent::init()
{
    m_buffer = std::make_unique<AudioBuffer<float>>(1, k_bufferSize);
    m_buffer->clear();

    startTimerHz(50);
}

void PhantomOscilloscopeComponent::paint(Graphics& graphics)
{
    m_isPainting = true;

    graphics.fillAll(Colours::transparentBlack);

    const int numSamples = m_buffer->getNumSamples();
    const float* reader = m_buffer->getReadPointer(0, 0);

    const float xScale = (float) getWidth() / (float) k_bufferSize * 2.0f;
    const float yScale = (float) getHeight() * 0.5f;

    float x1, y1, x2, y2;
    for(int i = 0; i < k_bufferSize - 1; i++)
    {
        const int idx = (m_bufferIdx + i) % (numSamples - 1);

        x1 = i * xScale;
        y1 = PhantomWaveshaper::clip(
            (reader[idx] + 1.0f) * yScale,
            0.0f,
            (float) getHeight()
        ) * 0.975f;

        x2 = (i + 1) * xScale;
        y2 = PhantomWaveshaper::clip(
            (reader[idx + 1] + 1.0f) * yScale,
            0.0f,
            (float) getHeight()
        ) * 0.975f;

        float brightness = (std::abs(reader[idx]) * 0.25f) + 0.75f;
        float saturation = (std::abs(reader[idx]) * 0.35f) + 0.65f;
        Colour colour = Consts::_STROKE_COLOUR
                                .withBrightness(brightness)
                                .withSaturation(saturation);

        graphics.setColour(colour);
        graphics.drawLine(x1, y1, x2, y2, k_strokeWidth);
    }

    m_isPainting = false;
}

void PhantomOscilloscopeComponent::resized()
{

}

void PhantomOscilloscopeComponent::timerCallback()
{
    repaint();
}

void PhantomOscilloscopeComponent::pushBuffer(AudioBuffer<float>& buffer)
{
    if(m_isPainting)
        return;

    const float* reader = buffer.getReadPointer(0, 0);
    const int numToCopy = buffer.getNumSamples();
    m_buffer->copyFrom(0, m_bufferIdx, reader, numToCopy);

    m_bufferIdx += numToCopy;
    m_bufferIdx %= k_bufferSize;
}
