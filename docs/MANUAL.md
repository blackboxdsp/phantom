# Manual

Thanks for checking out Phantom! The synth has around 50 parameters, which is a lot to interact with. For that reason, having a readable and accessible manual will be helpful for everyone in learning how to use it.

## What is Phantom?

Phantom is a synthesizer plugin that implements [_phase distortion_](https://en.wikipedia.org/wiki/Phase_distortion) as a means of generating sound. According to Wikipedia, phase distortion is the...

> change in the shape of the waveform, that occurs when (a) a filter's phase response is not linear over the frequency range of interest, that is, the phase shift introduced by a circuit or device is not directly proportional to frequency, or (b) the zero-frequency intercept of the phase-frequency characteristic is not 0 or an integral multiple of 2π radians

That gets pretty technical pretty fast, but in its essence phase distortion is applying an effect of distortion where the phase, rather than being read continuously in a linear fashion, is calculated according to some non-linear function. In the historical [Casio CZ-series](https://en.wikipedia.org/wiki/Casio_CZ_synthesizers) synths, these functions were piecewise functions typically splitting the domain of [0, 2π] into quarters and running random smaller linear functions. What's even better is that all of the interesting sounds were generated from doing that to a sine-wave alone.

## How does it work?

The following sections describe the various audio components of the synthesizer (plus their respective parameters) in the order that they are displayed in the GUI from left to right, top to bottom.

### Amplifier

The amplifier contains just the means to adjust the final output level (for the moment).

- __Level__: adjusts the final volume output with a range of [-30dB, 6dB].

### Oscillators

The oscillators are responsible for generating the sine-wave output and contain the common oscillator parameters with the exception of the waveform selection (in the phasor component).

- __Osc Sync__: syncs the second oscillator to the first when ON (value = 1)   
- __Osc Range__: sets the frequency range of the oscillator (in the tradional nature of organ stops)
- __Osc Coarse__: coarsely adjusts the oscillator frequency in tenths of a semitone with a range of -12.0 semitones to +12.0 semitones
- __Osc Fine__: finely adjusts the oscillator frequency in cents with a range of -100 cents to +100 cents
- __Osc Shape Int__: applies waveshaper effect to the oscillator (+)
- __Osc Mod Depth__: modulates oscillator frequency according to the depth of the modulation source (+/-)
- __Osc Mod Source__: selects between envelope generator (value = 0) and LFO (value = 1) as a modulation source

### Phasors

The phasors are the key component in Phantom's synthesis technique, effectively mapping the phase to a different shape (usually non-linear). This results in a sound that often sounds like anything but a sine-wave.

- __Phasor Shape__: selects the particular phase distortion function resulting in a different sounding waveform*
- __Phasor EG Int__: applies modulation from the envelope generator (+) 
- __Phasor LFO Int__: applies modulation from the LFO (+)

\* At the moment, the synth only contains the function for a sawtooth waveform. I have looked at adding the other typical waveforms and other more unusual ones, but have not settled on any yet. More waveforms are next on my list!

### Mixer

The mixer is responsible for summing the oscillator signals along with some additional effects.

- __Mixer Osc Balance__: balances mix between oscillators 1 and 2
- __Mixer Amp Gain__:  adjusts gain going into the filter (can be "overdriven")
- __Mixer Ring Mod__: adds ring modulation (multiplies oscillator 1's frequency by oscillator 2's) to the signal
- __Mixer Noise__: adds random noise to the signal

### Filter

The filter is a standard filter at a set slope of 12dB per octave with support filter in low-pass, band-pass, and high-pass modes.

- __Filter Cutoff__: controls the frequency in which the filter is being applied at with a range of [20Hz, 20KHz]
- __Filter Resonance__: controls the resonance of the filter (I _feel_ like it's nearly self-resonating...)
- __Filter Drive__: applies waveshaper distortion to the signal (post-filter)
- __Filter Mode__: selects the particular filter mode between low-pass, band-pass, and high-pass
- __Filter EG Mod Depth__: applies modulation from the envelope generator (+/-)
- __Filter LFO Mod Depth__: applies modulation from the LFO (+/-)

### Low-Frequency Oscillator (LFO)

The LFO provides interesting sonic possibilities being able to change other parameters over time. In the future I'd like to figure out a JUCE mod-matrix system to use in affording even more flexibility for the user.

- __LFO Rate__: controls the rate (frequency) that the LFO is running at with a range of [0.1Hz, 100Hz]
- __LFO Shape__: selects the particular LFO shape (waveform) to use (sine = 0, triangle = 1, saw = 2, square = 3, s+h = 4)

### Envelope Generators (EGs)

The EGs, like the LFO, apply change over time to other parameters, however they are most often triggered by note on/off events and apply a non-repeating modulation (unless there is capability for looping envelopes). 

- __EG Attack__: controls the attack time of the envelope with a range of [0.01s, 10s]
- __EG Decay__: controls the decay time of the envelope with a range of [0.01s, 2s]
- __EG Sustain__: controls the sustain level of the envelope with a range of [-60dB, 0dB]
- __EG Release__: controls the release time of the envelope with a range of [0.01s, 20s]

## Troubleshooting

If you discover a bug, it crashes, i.e. anything happens, I'd love to check it out and see what potential solutions exist to fix it. The easiest way to let me know of an issue is by [creating one](https://github.com/blackboxdsp/phantom/issues/new) on Phantom's GitHub repository.
