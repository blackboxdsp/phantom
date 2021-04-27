/*
  ==============================================================================

    PhantomOscilloscope.cpp
    Created: 12 Apr 2021 17:56:42
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscilloscope.h"
#include "PhantomUtils.h"
#include "PhantomWaveshaper.h"

PhantomOscilloscope::PhantomOscilloscope()
{
    startTimerHz(30);
}

PhantomOscilloscope::~PhantomOscilloscope()
{

}

void PhantomOscilloscope::paint(Graphics& graphics)
{
    const float width = getWidth();
    const float height = getHeight();

    graphics.setColour(Colours::transparentBlack);
    graphics.fillAll();

    Path samplePath;

    samplePath.startNewSubPath(m_point.x , m_point.y);

    for(int i = 0; i < m_buffer.size(); i++)
    {
        m_point.x = i * width / m_buffer.size();
        m_point.y = height / 2.0f + PhantomWaveshaper::clip(m_buffer[i], -1.0f, 1.0f) * height * 0.48f;

        if(i == 0)
            samplePath.startNewSubPath(m_point.x, m_point.y);
        else
            samplePath.lineTo(m_point.x, m_point.y);
    }

    // NOTE: Only the x value is reset here because we have reached the end of the buffer,
    // meaning that we must reset to the beginning again however keeping the y value allows
    // the visual to be drawn continuously from the previous buffer.
    m_point.x = 0.0f;

    graphics.setColour(Consts::_FILL_START_COLOUR);
    graphics.strokePath(samplePath, PathStrokeType(m_strokeWidth));
}

void PhantomOscilloscope::resized()
{

}

void PhantomOscilloscope::timerCallback()
{
    repaint();
}

void PhantomOscilloscope::pushBuffer(AudioSampleBuffer& buffer)
{
    if(m_bufferIndex == 0)
        m_buffer.clearQuick();

    for(int i = 0; i < buffer.getNumSamples(); i++)
    {
        m_buffer.insert(m_bufferIndex, buffer.getSample(0, i));

        m_bufferIndex = (int) fmod((float) m_bufferIndex++, (float) BUFFER_SIZE);
    }
}
