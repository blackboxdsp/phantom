/*
  ==============================================================================

    PhantomSynth.cpp
    Created: 31 Jan 2020 9:33:53pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PhantomSynth.h"

//==============================================================================
PhantomSynthVoice::PhantomSynthVoice()
{

}

PhantomSynthVoice::~PhantomSynthVoice()
{

}

bool PhantomSynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSynthSound*> (sound) != nullptr;
}

void PhantomSynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void PhantomSynthVoice::pitchWheelMoved(int newPitchWheelValue = 0)
{

}

void PhantomSynthVoice::renderNextBlock(AudioSampleBuffer& buffer, int startSample, int numSamples)
{
    if (phaseDelta != 0.0)
    {
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin(currentPhase) * level * tailOff);

                for (auto i = buffer.getNumChannels(); --i >= 0;)
                    buffer.addSample(i, startSample, currentSample);

                currentPhase += phaseDelta;
                startSample++;

                tailOff *= 0.99;

                if (tailOff <= 0.005)
                {
                    clearCurrentNote();

                    phaseDelta = 0.0;
                }
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin(currentPhase) * level);

                for (auto i = buffer.getNumChannels(); --i >= 0;)
                    buffer.addSample(i, startSample, currentSample);

                currentPhase += phaseDelta;
                startSample++;
            }
        }
    }
}

void PhantomSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    // reset phase variables
    currentPhase = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;

    auto frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = frequency / getSampleRate();

    phaseDelta = cyclesPerSample * MathConstants<double>::twoPi;
}

void PhantomSynthVoice::stopNote(float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff <= 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        phaseDelta = 0.0;
    }
}

//==============================================================================
PhantomSynthAudioSource::PhantomSynthAudioSource(MidiKeyboardState& keyState)
    : keyboardState(keyState)
{
    for (auto i = 0; i < 2; i++)
        synth.addVoice(new PhantomSynthVoice());
    synth.addSound(new PhantomSynthSound());
}

PhantomSynthAudioSource::~PhantomSynthAudioSource()
{

}

void PhantomSynthAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    MidiBuffer incomingMidi;
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);
    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);
}

void PhantomSynthAudioSource::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void PhantomSynthAudioSource::releaseResources()
{

}

void PhantomSynthAudioSource::setUsingPhantomSynthSound()
{
    synth.clearSounds();
}
