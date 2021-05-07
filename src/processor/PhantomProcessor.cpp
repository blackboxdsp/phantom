/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#include "PhantomProcessor.h"

#include "../editor/PhantomEditor.h"
#include "../utils/PhantomData.h"

PhantomAudioProcessor::PhantomAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     :  m_parameters(*this, nullptr, Identifier("Phantom"), CreateParameterLayout()),
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
    m_presetManager = std::make_unique<PhantomPresetManager>(m_parameters);

    m_synth = std::make_unique<PhantomSynth>(m_parameters);
    m_amp = std::make_unique<PhantomAmplifier>(m_parameters);
}

PhantomAudioProcessor::~PhantomAudioProcessor()
{
    m_presetManager = nullptr;

    m_synth = nullptr;
    m_amp = nullptr;
}

const String PhantomAudioProcessor::getName() const
{
    return Consts::_PLUGIN_NAME;
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

void PhantomAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    int numChannels = jmin(getMainBusNumInputChannels(), getMainBusNumOutputChannels());
    m_synth->init((float) sampleRate, samplesPerBlock, numChannels);
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

    m_synth->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    m_amp->apply(buffer);

    PhantomAudioProcessorEditor* editor = static_cast<PhantomAudioProcessorEditor*>(getActiveEditor());
    if(editor)
    {
        editor->m_phantomOscilloscope->pushBuffer(buffer);
        editor->m_phantomAnalyzer->pushBuffer(buffer);
    }
}

bool PhantomAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* PhantomAudioProcessor::createEditor()
{
    return new PhantomAudioProcessorEditor(*this, m_parameters);
}

void PhantomAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(m_parameters.state.createXml());
    xml = m_presetManager->saveMetadataToXml(std::move(xml));
    copyXmlToBinary(*xml, destData);
}

void PhantomAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if(xml.get() != nullptr)
        m_presetManager->loadStateFromXml(std::move(xml));
}

PhantomPresetManager& PhantomAudioProcessor::getPresetManager()
{
    return *m_presetManager;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhantomAudioProcessor();
}
