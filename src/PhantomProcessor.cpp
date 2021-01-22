/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#include "PhantomEditor.h"
#include "PhantomProcessor.h"

//==============================================================================
PhantomAudioProcessor::PhantomAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     :  m_parameters(*this, nullptr, Identifier("Phantom"), createParameterLayout()),
        AudioProcessor(BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    p_level = m_parameters.getRawParameterValue("level");

    m_phantom = new PhantomSynth(m_parameters);
}

PhantomAudioProcessor::~PhantomAudioProcessor()
{
    m_phantom->clear();

    p_level = nullptr;
}

//==============================================================================
AudioProcessorValueTreeState::ParameterLayout PhantomAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    auto oscillatorRange = std::make_unique<AudioParameterFloat>(
        "oscillatorRange", "Osc Range",
        NormalisableRange<float>(0.0f, 3.0f, 1.0f),
        2.0f
    );
    params.push_back(std::move(oscillatorRange));

    auto oscillatorTune = std::make_unique<AudioParameterFloat>(
        "oscillatorTune", "Osc Tune",
        NormalisableRange<float>(-12.0f, 12.0f, 0.1f),
        0.0f    
    );
    params.push_back(std::move(oscillatorTune));

    auto level = std::make_unique<AudioParameterFloat>(
        "level", "Level",
        NormalisableRange<float>(-48.0f, 12.0f, 0.1f, getSkewFactor(-48.0f, 12.0f, 0.0f), false),
        0.0f);
    params.push_back(std::move(level));

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

void PhantomAudioProcessor::setCurrentProgram(int index)
{
}

const String PhantomAudioProcessor::getProgramName(int index)
{
    return {};
}

void PhantomAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void PhantomAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);

    m_phantom->setCurrentPlaybackSampleRate(sampleRate);
}

void PhantomAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PhantomAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if(layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if(layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PhantomAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();

    const int startSample = 0;
    const int numSamples = buffer.getNumSamples();

    m_phantom->renderNextBlock(buffer, midiMessages, startSample, numSamples);

    float gain = powf(2, *p_level / 6);
    if(gain != m_previousGain)
    {
        buffer.applyGainRamp(startSample, numSamples, m_previousGain, gain);
        m_previousGain = gain;
    }
    else 
    {
        buffer.applyGain(gain);
    }
}

//==============================================================================
bool PhantomAudioProcessor::hasEditor() const
{
    return true; //(change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PhantomAudioProcessor::createEditor()
{
    return new PhantomAudioProcessorEditor(*this, m_parameters);
}

//==============================================================================
void PhantomAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(m_parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PhantomAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState.get() != nullptr)
    {
        if(xmlState->hasTagName(m_parameters.state.getType()))
        {
            m_parameters.replaceState(ValueTree::fromXml(*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhantomAudioProcessor();
}

//==========================================================================
float PhantomAudioProcessor::getSkewFactor(float start, float end, float center)
{
    return std::log((0.5f)) / std::log((center - start) / (end - start));
}
