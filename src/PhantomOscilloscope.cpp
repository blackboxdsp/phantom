/*
  ==============================================================================

    PhantomOscilloscope.cpp
    Created: 12 Apr 2021 17:56:42
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscilloscope.h"
#include "PhantomUtils.h"

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

    float x = 0.0f;
    float y = m_buffer[0] * height * 0.5f;
    samplePath.startNewSubPath(x , y);

    for(int i = 0; i < m_buffer.size(); i++)
    {
        x = i * width / m_buffer.size();
        y = height / 2.0f + m_buffer[i] * height * 0.5f;

        if(i == 0)
            samplePath.startNewSubPath(x, y);
        else
            samplePath.lineTo(x , y);
    }

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
