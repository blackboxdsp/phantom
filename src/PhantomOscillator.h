/*
  ==============================================================================

    PhantomOscillator.h
    Created: 20 Jan 2021 21:17:28
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomPhasor.h"
#include "PhantomWaveshaper.h"

/**
 * The audio component for an oscillator, the main "sound generator" 
 * in the synth. In most synths, it would be here that would produce 
 * the interesting waves, but because Phantom uses *phase distortion* 
 * this oscillator only produces a sine wave.
 */
class PhantomOscillator 
{
public:
    PhantomOscillator(AudioProcessorValueTreeState&, int);
    ~PhantomOscillator();

    /**
     * Resets the oscillator parameters back to default state.
     */
    void reset();

    /**
     * Updates the oscillators parameters.
     * @param midiNoteNumber The pitch value from the note MIDI data.
     * @param sampleRate The sample rate to use in determining the frequency.
     */
    void update(int midiNoteNumber, float sampleRate) noexcept;
    
    /**
     * Update the oscillator's phase specifically.
     * @param phase The value to use in updating the phase.
     */
    void updatePhase(float phase) noexcept;

    /**
     * Reads the oscillator's phase, useful for hard syncing 1+ oscillators.
     * @returns The current phase value for the oscillator.
     */
    float readPhase() noexcept;

    /**
     * Computes the next sample value for the oscillator.
     * @param oscEgMod The MOD envelope generator modulation value for the oscillator.
     * @param oscLfoMod The LFO modulation value for the oscillator.
     * @param phaseEgMod The envelope generator modulation value for the phasor.
     * @param phaseLfoMod The LFO modulation value for the phasor.
     * @returns The next sample value for the oscillator with modulation applied.
     */
    float evaluate(float oscEgMod, float oscLfoMod, float phaseEgMod, float phaseLfoMod) noexcept;

    /**
     * Converts the pitch value from a note's MIDI data to frequency (Hz).
     * @param midiNote The MIDI pitch value to convert.
     * @returns The converted MIDI pitch value to frequency (Hz).
     */
    float midiNoteToFrequency(float midiNote) noexcept;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscillator)

    /**
     * Initializes the `AudioProcessorValueTreeState` oscillator parameters.
     */
    void initParameters();

    /**
     * Initializes the wavetable (only sine).
     */
    void initWavetable();

    /**
     * Update the oscillator's frequency.
     */
    void updateFrequency() noexcept;

    /**
     * Update the oscillator's phase delta.
     */
    void updatePhaseDelta() noexcept;

    /**
     * Update the oscillator's phase delta for specific frequency.
     * @param frequency The specific frequency to use in calculating the phase delta.
     */
    void updatePhaseDelta(float frequency) noexcept;

    /** The wavetable object, which is just an array of floats. */
    Array<float> m_wavetable;

    /** The unique pointer to the oscillator's phasor, for applying phase distortion. */
    std::unique_ptr<PhantomPhasor> m_phasor;

    /**
     * The unique pointer to the oscillator's waveshaper, for applying slight
     * waveshaping (mostly distortion).
     */
    std::unique_ptr<PhantomWaveshaper> m_waveshaper;
    
    AudioProcessorValueTreeState& m_parameters;

    /** The atomic parameter pointer for the oscillator's range. */
    std::atomic<float>* p_oscRange;

    /** The atomic parameter pointer for the oscillator's coarse tune. */
    std::atomic<float>* p_oscCoarseTune;

    /** The atomic parameter pointer for the oscillator's fine tune. */
    std::atomic<float>* p_oscFineTune;

    /** The atomic parameter pointer for the oscillator's modulation depth. */
    std::atomic<float>* p_modDepth;

    /** The atomic parameter pointer for the oscillator's modulation source. */
    std::atomic<float>* p_modSource;

    /** The atomic parameter pointer for the oscillator's shape intensity. */
    std::atomic<float>* p_shapeInt;

    /**
     * The oscillator identifier, useful in assigning the correct `AudioProcessorValueTreeState` 
     * parameters.
     */
    int m_oscNumber;

    /** The sampling rate, useful for determining the phase delta / frequency. */
    float m_sampleRate;

    /** The maximum exponent value for pitch modulation. */
    const int k_modExpoThreshold = 5;

    /** The phase value which determines the index to read the wavetable at. */
    float m_phase = 0.0f;

    /**
     * The phase delta is the amount to increment the phase after each read, 
     * which ultimately determines the oscillator's output frequency.
     */
    float m_phaseDelta = 0.0f;

    /** The MIDI pitch value for the last played (possibly current) note. */
    int m_midiNoteNumber = -1;

    /** The frequency value for the last played (possibly current) note. */
    float m_frequency = 0.0f;
};
