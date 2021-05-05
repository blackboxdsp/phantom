/*
  ==============================================================================

    PhantomVoice.h
    Created: 20 Jan 2021 20:59:55
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomEnvelopeGenerator.h"
#include "PhantomFilter.h"
#include "PhantomLFO.h"
#include "PhantomMixer.h"
#include "PhantomOscillator.h"

/**
 * The class overriding JUCE's `SynthesiserVoice`, which is necessary for creating
 * synthesizers. Here there are methods for applying all components of each voice
 * to the `AudioBuffer` and starting / stopping notes.
 */
class PhantomVoice : public SynthesiserVoice
{
public:
    PhantomVoice(AudioProcessorValueTreeState&, dsp::ProcessSpec&);
    ~PhantomVoice();

    /**
     * Called to let the voice know that the pitch wheel has been moved.
     * @param pitchWheelPos The new pitch wheel position value.
     */
    void pitchWheelMoved(int pitchWheelPos) { }

    /**
     * Called to let the voice know that a MIDI controller has been moved.
     * @param controllerNum The new controller number.
     * @param controllerValue The new controller value.
     */
    void controllerMoved(int controllerNumber, int controllerValue) { }

    /**
     * Checks for a `null_ptr`
     * @param sound A raw `SynthesiserSound` pointer to check.
     * @returns A boolean value that's `true` if the pointer isn't null.
     */
    bool canPlaySound(SynthesiserSound* sound) override;

    /**
     * Triggers the envelope generators and updates oscillators.
     * @param midiNoteNumber The pitch value from the note MIDI data.
     * @param velocity The velocity value from the note MIDI data.
     * @param sound A raw `SynthesiserSound` pointer. 
     * @param currentPitchWheelPosition The position of the pitch wheel.
     */
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override;

    /**
     * Stops envelope generators and clears the current note.
     * @param velocity The velocity value from the note MIDI data.
     * @param allowTailOff Allows the note's tail to sound.
     */
    void stopNote(float velocity, bool allowTailOff) override;

    void clear();

    /**
     * Applies all components of the `PhantomSynth` engine to the audio buffer.
     * @param buffer A reference to the audio buffer to write to.
     * @param startSample The sample index to begin with.
     * @param numSamples The number of samples to write.
     */
    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomVoice)

    /**
     * Resets phase of secondary oscillator if given value is less than or equal to `k_oscSyncPhaseThreshold`.
     * @param valueToRead The value to check for phase equality.
     */
    void handleOscSync(float valueToRead) noexcept;

    /**
     * The unique pointer for the amplifier envelope generator.
     */
    std::unique_ptr<PhantomEnvelopeGenerator> m_ampEg;

    /**
     * The unique pointer for the phasor envelope generator.
     */
    std::unique_ptr<PhantomEnvelopeGenerator> m_phaseEg;

    /**
     * The unique pointer for the filter envelope generator.
     */
    std::unique_ptr<PhantomEnvelopeGenerator> m_filterEg;

    /**
     * The unique pointer for the mod envelope generator.
     */
    std::unique_ptr<PhantomEnvelopeGenerator> m_modEg;

    /**
     * The unique pointer for the first LFO.
     */
    std::unique_ptr<PhantomLFO> m_lfo01;

    /**
     * The unique pointer for the second LFO.
     */
    std::unique_ptr<PhantomLFO> m_lfo02;

    /**
     * The unique pointer for the primary oscillator, which is used to sync 
     * the secondary oscillator (if sync is ON).
     */
    std::unique_ptr<PhantomOscillator> m_primaryOsc;
    
    /**
     * The unique pointer for the secondary oscillator, which is synced to the 
     * primary oscillator (if sync is ON).
     */ 
    std::unique_ptr<PhantomOscillator> m_secondaryOsc;

    /**
     * The unique pointer for the mixer, which is used to handle the oscillator
     * outputs.
     */
    std::unique_ptr<PhantomMixer> m_mixer;

    /**
     * The unique pointer for the filter.
     */
    std::unique_ptr<PhantomFilter> m_filter;

    AudioProcessorValueTreeState& m_parameters;

    /**
     * The atomic parameter pointer for oscillator sync.
     */
    std::atomic<float>* p_oscSync;

    /**
     * Integer value for the current note MIDI pitch value. 
     * NOTE: 60 corresponds to middle C (C4).
     */
    int m_midiNoteNumber = 60;
    
    /**
     * Boolean value for if the oscillator sync is turned on (true) or off (false).
     */
    bool m_oscSyncToggle = false;

    /**
     * Constant float value for checking zero-crossings in phase. This value is based on the wavetable implementation 
     * meaning that this variables range is within the size of that wavetable.
     */
    const float k_oscSyncPhaseThreshold = 0.2f;

    bool m_isNoteOn = false;

    bool m_isNoteCleared = true;
    
    /**
     * Float value for velocity of a note, useful in calling `stopNote()` at any time.
     */
    float m_velocity = -1.0f;

    /**
     * Multiplier for smoothing abrupt releases of notes.
     */
    float m_tailOff = 0.0f;
};
