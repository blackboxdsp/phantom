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
    void pushBuffer(AudioSampleBuffer &buffer);

    /**
     * Enumerator with data for the size of the buffer to use 
     * in the component's display.
     * @property BUFFER_ORDER The amount to bitshift the FFT_SIZE.
     * @property BUFFER_SIZE The value of 1 bitshifted by the FFT_ORDER
     */
    enum
    {
        BUFFER_ORDER = 11,
        BUFFER_SIZE = 1 << BUFFER_ORDER, // 2048
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscilloscope)

    /**
     * The buffer containing samples for the oscilloscope.
     */
    Array<float> m_buffer;

    /**
     * The index value corresponding to the buffer.
     */
    int m_bufferIndex = 0;

    /**
     * The width of the stroke path.
     */
    const float m_strokeWidth = 3.0f;

    Point<float> m_point = { 0.0f, 0.0f };
};

/**
 * Small utility struct for easier coordinate data.
 */
template<class T>
struct Point
{
    T x, y;
};
