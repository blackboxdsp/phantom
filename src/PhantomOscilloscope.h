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
     * CAUTION: This method is called from within the audio thread so it must be real-time safe.
     * @param buffer A reference to the buffer data that will be inserted.
     */
    void pushBuffer(AudioSampleBuffer &buffer) noexcept;

    inline void pushNextSample(float sample) noexcept;

    /**
     * Enumerator with data for the size of the buffer to use 
     * in the component's display.
     * @property BUFFER_SIZE The size of the buffer, which is 1 bitshifted by n bits (or 2^n) where n = 10.
     * @property OUTPUT_SIZE Exactly half of the buffer size.
     */
    enum
    {
        BUFFER_SIZE = 1 << 10,
        OUTPUT_SIZE = BUFFER_SIZE / 2
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscilloscope)

    /**
     * The buffer containing samples for the oscilloscope.
     */
    // Array<float> m_buffer;

    float m_outputData[OUTPUT_SIZE];

    unsigned int m_outputDataIdx = 0;

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
