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

PhantomOscilloscope::PhantomOscilloscope()
{
    init();
}

PhantomOscilloscope::~PhantomOscilloscope()
{
    stopTimer();

    m_buffer = nullptr;
}

void PhantomOscilloscope::init()
{
    m_buffer = std::make_unique<AudioBuffer<float>>(1, k_bufferSize);
    m_buffer->clear();

    startTimerHz(50);
}

void PhantomOscilloscope::paint(Graphics& graphics)
{
    m_isPainting = true;

    graphics.fillAll(Colours::transparentBlack);

    const float* reader = m_buffer->getReadPointer(0, 0);

    const float xScale = (float) getWidth() / (float) k_bufferSize * 2.0f;
    const float yScale = (float) getHeight() * 0.5f;

    const int length = k_bufferSize - 1;

    float x1, y1, x2, y2;
    for(int i = 0; i < length; i++)
    {
        x1 = i * xScale;
        y1 = PhantomWaveshaper::clip(
            (reader[i] + 1.0f) * yScale,
            0.0f,
            (float) getHeight()
        ) * 0.975f;

        x2 = (i + 1) * xScale;
        y2 = PhantomWaveshaper::clip(
            (reader[i + 1] + 1.0f) * yScale,
            0.0f,
            (float) getHeight()
        ) * 0.975f;

        float brightness = (std::abs(reader[i]) * 0.25f) + 0.75f;
        float saturation = (std::abs(reader[i]) * 0.35f) + 0.65f;
        Colour colour = Consts::_STROKE_COLOUR
                                .withBrightness(brightness)
                                .withSaturation(saturation);

        graphics.setColour(colour);
        graphics.drawLine(x1, y1, x2, y2, k_strokeWidth);
    }

    m_isPainting = false;
}

void PhantomOscilloscope::resized()
{

}

void PhantomOscilloscope::timerCallback()
{
    repaint();
}

void PhantomOscilloscope::pushBuffer(AudioBuffer<float>& buffer)
{
    if(m_isPainting)
        return;

    const float* reader = buffer.getReadPointer(0, 0);
    const int numToCopy = buffer.getNumSamples();
    m_buffer->copyFrom(0, m_bufferIdx, reader, numToCopy);

    m_bufferIdx += numToCopy;
    m_bufferIdx %= k_bufferSize;
}
