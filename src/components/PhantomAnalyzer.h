/*
  ==============================================================================

    PhantomAnalyzer.h
    Created: 12 Apr 2021 16:27:57
    Author:  Matthew Maxwell

  ==============================================================================
*/

#ifndef _PHANTOM_ANALYZER_COMPONENT_H
#define _PHANTOM_ANALYZER_COMPONENT_H

#include "../interfaces/IComponent.h"

/**
 * The GUI component for displaying the frequency information of the signal.
 */
class PhantomAnalyzerComponent : public IComponent,
                                 private Timer
{
public:
    PhantomAnalyzerComponent();
    ~PhantomAnalyzerComponent();

    void init() override;

    void paint(Graphics& g) override;
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
    void pushBuffer(AudioSampleBuffer& buffer) noexcept;

    /**
     * Inserts single sample point into the buffer.
     * CAUTION: This method is called from within the audio thread so it must be real-time safe.
     * @param sample The sample point value, ideally in the range of [-1.0f, 1.0f].
     */
    inline void pushNextSample(float sample) noexcept;

    /**
     * Enumerator with data for the size of the buffer to use 
     * in the component's display.
     * @property FFT_ORDER The amount to bitshift the FFT_SIZE.
     * @property FFT_SIZE The value of 1 bitshifted by the FFT_ORDER
     * @property OUTPUT_SIZE FFT_SIZE divided by 2
     */
    enum
    {
        FFT_ORDER = 11,
        FFT_SIZE = 1 << FFT_ORDER,    // 2048
        OUTPUT_SIZE = FFT_SIZE / 2    // 1024
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAnalyzerComponent)
  
    /**
     * The `FFT` object, specifically a _forward_ one meaning that
     * it uses real-to-complex two-dimensional transformations.
     */
    dsp::FFT m_forwardFFT;

    /**
     * The windowing function to use in the implementation.
     */
    dsp::WindowingFunction<float> m_window;

    /**
     * `float` array containing incoming audio data in samples.
     */
    float m_FFTQueue[FFT_SIZE];

    /**
     * `float` array containing results of FFT calculations.
     */
    float m_FFTData[2 * FFT_SIZE];

    /**
     * `float` array containing the output data to use in the display.
     */
    float m_outputData[OUTPUT_SIZE];

    /**
     * To keep count of the amount of samples in the queue.
     */
    unsigned int m_FFTQueueIndex = 0;

    /**
     * Determines if the next audio block is ready to be processed.
     */
    bool m_isNextFFTBlockReady = false;
};

#endif
