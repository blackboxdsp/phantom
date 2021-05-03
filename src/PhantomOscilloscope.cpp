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

void PhantomOscilloscope::init(float sampleRate, int samplesPerBlock)
{
    m_sampleRate = sampleRate;

    m_buffer.setSize(1, (int) m_sampleRate);
    m_buffer.clear();

    m_bufferIdx.store(0);
}

void PhantomOscilloscope::paint(Graphics& graphics)
{
    const float width = getWidth();
    const float height = getHeight();

    int bufferIndex = m_bufferIdx.load();

    graphics.setColour(Colours::transparentBlack);
    graphics.fillAll();

    Path path;
    path.startNewSubPath(m_drawPoint);

    for(int i = 0; i < k_drawSize; i++)
    {
        int idx = (bufferIndex + m_buffer.getNumSamples() - (k_drawSize - i)) % m_buffer.getNumSamples();

        float x = (float) (i + 1) / k_drawSize * width;
        float y = (m_buffer.getSample(0, idx) * height * 0.5f) + (height * 0.5f);

        m_drawPoint.setXY(
            x,
            PhantomWaveshaper::clip(
                (y + m_drawPoint.getY()) / 2.0f,
                0.0f, height * 0.9f
            )
        );

        path.lineTo(m_drawPoint);
    }

    m_drawPoint.setX(0.0f);

    graphics.setColour(Consts::_FILL_START_COLOUR);
    graphics.strokePath(path, PathStrokeType(k_strokeWidth));
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
    const int writeIdx = m_bufferIdx.load();
    const int numTotalSamples = buffer.getNumSamples();
    const int numAvailableSamples = m_buffer.getNumSamples() - writeIdx;

    if(numAvailableSamples >= numTotalSamples)
    {
        m_buffer.copyFrom(0, m_bufferIdx, buffer.getReadPointer(0), numTotalSamples);
    }
    else
    {
        m_buffer.copyFrom(0, m_bufferIdx, buffer.getReadPointer(0), numAvailableSamples);
        m_buffer.copyFrom(0, 0, buffer.getReadPointer(0, numAvailableSamples), numTotalSamples - numAvailableSamples);
    }

    if(numAvailableSamples > numTotalSamples)
        m_bufferIdx.store(writeIdx + numTotalSamples);
    else
        m_bufferIdx.store(numTotalSamples - numAvailableSamples);

}
