/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PhantomProcessor.h"
#include "PhantomEditor.h"

//==============================================================================
PhantomAudioProcessor::PhantomAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : parameters(*this, nullptr, Identifier("Phantom"), createParameterLayout()),
      AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    // clear and add voice(s)
    phantomSynth.clearVoices();
    for(auto i = 0; i < 1; i++)
        phantomSynth.addVoice(new PhantomVoice(parameters));

    // clear and add sound(s)
    phantomSynth.clearSounds();
    phantomSynth.addSound(new PhantomSound());
}

PhantomAudioProcessor::~PhantomAudioProcessor()
{
    phantomSynth.clearSounds();
    phantomSynth.clearVoices();
}

AudioProcessorValueTreeState::ParameterLayout PhantomAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    // ATTACK
    auto p_attack = std::make_unique<AudioParameterFloat>(
        "attack", "Attack",
        NormalisableRange<float>(0.001f, 20.0f, 0.01f, getSkewFactor(0.001f, 15.0f, 1.0f)),
        0.001f);
    params.push_back(std::move(p_attack));

    // DECAY
    auto p_decay = std::make_unique<AudioParameterFloat>(
        "decay", "Decay",
        NormalisableRange<float>(0.001f, 60.0f, 0.01f, getSkewFactor(0.001f, 30.0f, 1.0f)),
        0.6f);
    params.push_back(std::move(p_decay));

    // SUSTAIN
    auto p_sustain = std::make_unique<AudioParameterFloat>(
        "sustain", "Sustain",
        NormalisableRange<float>(-60.0f, 0.0f, 0.1f),
        0.0f);
    params.push_back(std::move(p_sustain));

    // RELEASE
    auto p_release = std::make_unique<AudioParameterFloat>(
        "release", "Release", 
        NormalisableRange<float>(0.001f, 60.0f, 0.01f, getSkewFactor(0.001f, 30.0f, 1.0f)),
        0.05f);
    params.push_back(std::move(p_release));

    return { params.begin(), params.end() };
}

//==============================================================================
const String PhantomAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PhantomAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PhantomAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PhantomAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PhantomAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PhantomAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PhantomAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PhantomAudioProcessor::setCurrentProgram (int index)
{
}

const String PhantomAudioProcessor::getProgramName (int index)
{
    return {};
}

void PhantomAudioProcessor::changeProgramName (int index, const String& newName)
{

}

//==============================================================================
void PhantomAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // ignore unused samples from last key press
    ignoreUnused(samplesPerBlock);

    // set phantom synth settings 
    phantomSynth.setCurrentPlaybackSampleRate(sampleRate);
    for(auto i = 0; i < phantomSynth.getNumVoices(); i++)
        phantomSynth.getVoice(i)->setCurrentPlaybackSampleRate(sampleRate);
}

void PhantomAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PhantomAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PhantomAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    phantomSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool PhantomAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PhantomAudioProcessor::createEditor()
{
    return new PhantomAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void PhantomAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PhantomAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(ValueTree::fromXml(*xmlState));
        }
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhantomAudioProcessor();
}

//==============================================================================
float PhantomAudioProcessor::getSkewFactor(float start, float end, float center)
{
    return std::log((0.5f)) / std::log((center - start) / (end - start));
}
