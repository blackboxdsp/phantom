/*
  ==============================================================================

    PhantomOscilloscope.h
    Created: 12 Apr 2021 17:56:42
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_OSCILLOSCOPE_COMPONENT_H
#define _PHANTOM_OSCILLOSCOPE_COMPONENT_H

#include "JuceHeader.h"

/**
 * The GUI component for displaying the amplitude information for the synthesizer
 * output.
 */
class PhantomOscilloscopeComponent : public Component,
                                     private Timer
{
public:
    PhantomOscilloscopeComponent();
    ~PhantomOscilloscopeComponent();

    void init();

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscilloscopeComponent)

    /** The unique pointer to the buffer containing samples for the oscilloscope. */
    std::unique_ptr<AudioBuffer<float>> m_buffer;


    /** The current buffer position, which is atomic since it is updated by the audio thread and read by the GUI thread. */
    unsigned int m_bufferIdx = 0;

    /** The buffer size to use in containing sample data. */
    const int k_bufferSize = 1 << 10;

    /** The width of the stroke to use in painting the samples. */
    const float k_strokeWidth = 1.8f;

    /** Lock for when the component is painting the samples. */
    bool m_isPainting = false;
};

#endif
