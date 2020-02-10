/*
  ==============================================================================

    PhantomOscilloscope.h
    Created: 9 Feb 2020 9:19:31pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class PhantomOscilloscope : public Component,
                            private Timer
{
public:
    //==========================================================================
    PhantomOscilloscope()   
    {
        startTimerHz(30);
    };

    ~PhantomOscilloscope()  
    {

    };

    //==========================================================================
    void paint(Graphics& g) override
    {
        const float width = getWidth();
        const float height = getHeight();

        g.setColour(Colours::transparentBlack);
        g.fillAll();

        float x = 0.0f;
        float y = outBuffer[0] * height * 0.5f;

        Path signalPath;
        signalPath.startNewSubPath(x, y);

        for (auto sample = 0; sample < outBuffer.size(); sample++)
        {
            x = sample * width / outBuffer.size();
            y = height / 2.0f + outBuffer[sample] * height * 0.5f;

            if (sample == 0)
                signalPath.startNewSubPath(x, y);
            else
                signalPath.lineTo(x, y);
        }

        g.setColour(pathFill);
        g.strokePath(signalPath, PathStrokeType(strokeWidth));
    }
    void resized() override
    {

    }
    void timerCallback() override
    {
        repaint();
    }

    //==========================================================================
    void readBuffer(AudioBuffer<float>& inBuffer)
    {
        if (bufferIndex == 0)
            outBuffer.clear();

        for (auto sample = 0; sample < inBuffer.getNumSamples(); sample++)
        {
            outBuffer.insert(bufferIndex, inBuffer.getSample(0, sample));
            bufferIndex = (int) fmod(bufferIndex++, bufferSize);
        }
    }

private:
    //==========================================================================
    // oscilloscope variables
    Array<float> outBuffer;
    int bufferIndex = 0;
    const int bufferSize = 1 << 11; // 2048
    const Colour pathFill = Colour::fromRGBA(204, 204, 204, 255);
    const float strokeWidth = 3.0f;

    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscilloscope)
};