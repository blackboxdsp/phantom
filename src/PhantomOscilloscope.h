/*
  ==============================================================================

    PhantomOscilloscope.h
    Created: 12 Apr 2021 17:56:42
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/**
 * The GUI component for displaying the amplitude information for the synthesizer
 * output.
 */
class PhantomOscilloscope : public Component,
                            private Timer
{
public:
    PhantomOscilloscope();
    ~PhantomOscilloscope();

    void init(float sampleRate, int samplesPerBlock);

    /**
     * Determines the GUI display of the oscilloscope component.
     * @param graphics The reference to the `Graphics` object.
     */
    void paint(Graphics &graphics) override;

    /**
     * Determines the layout of the oscilloscopes GUI components.
     */
    void resized() override;

    /**
     * Called when the timer hits zero and is reset.
     */
    void timerCallback() override;

    /**
     * Inserts data into the buffer to use for the display.
     * @param buffer A reference to the buffer data that will be inserted.
     */
    void pushBuffer(AudioBuffer<float>& buffer);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscilloscope)

    /**
     * The buffer containing samples for the oscilloscope.
     */
    AudioBuffer<float> m_buffer;

    /**
     * The current buffer position, which is atomic since it is updated by the audio thread and read by the GUI thread.
     */
    std::atomic<int> m_bufferIdx = 0;

    /**
     * The sample rate, useful for configuring the buffer.
     */
    float m_sampleRate = 0.0f;

    /**
     * A constant integer for the component canvas size (2 ^ n).
     */
    const int k_drawSize = 1 << 9;

    /**
     * The point representing the most recently drawn sample.
     */
    Point<float> m_drawPoint = Point<float>(0.0f, 0.0f);

    /**
     * The width of the stroke path.
     */
    const float k_strokeWidth = 3.0f;
};
