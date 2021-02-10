/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#include "PhantomEditor.h"
#include "PhantomProcessor.h"
#include "PhantomUtils.h"

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
    m_synth = new PhantomSynth(m_parameters);
    m_amp = new PhantomAmplifier(m_parameters);
}

PhantomAudioProcessor::~PhantomAudioProcessor()
{
    m_synth = nullptr;
    m_amp = nullptr;
}

//==============================================================================
AudioProcessorValueTreeState::ParameterLayout PhantomAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    // EGs

    // AMP EG

    auto ampEgAtk = std::make_unique<AudioParameterFloat>(
        Consts::_AMP_EG_ATK_PARAM_ID, Consts::_AMP_EG_ATK_PARAM_NAME,
        NormalisableRange<float>(0.01f, 10.0f, 0.01f, getSkewFactor(0.01f, 10.0f, 1.0f), false),
        Consts::_AMP_EG_ATK_DEFAULT_VAL
    );
    params.push_back(std::move(ampEgAtk));

    auto ampEgDec = std::make_unique<AudioParameterFloat>(
        Consts::_AMP_EG_DEC_PARAM_ID, Consts::_AMP_EG_DEC_PARAM_NAME,
        NormalisableRange<float>(0.01f, 2.0f, 0.01f, getSkewFactor(0.01f, 2.0f, 0.5f), false),
        Consts::_AMP_EG_DEC_DEFAULT_VAL
    );
    params.push_back(std::move(ampEgDec));

    auto ampEgSus = std::make_unique<AudioParameterFloat>(
        Consts::_AMP_EG_SUS_PARAM_ID, Consts::_AMP_EG_SUS_PARAM_NAME,
        NormalisableRange<float>(-60.0f, 0.0f, 0.1f, getSkewFactor(-60.0f, 0.0f, -30.0f), false),
        Consts::_AMP_EG_SUS_DEFAULT_VAL
    );
    params.push_back(std::move(ampEgSus));

    auto ampEgRel = std::make_unique<AudioParameterFloat>(
        Consts::_AMP_EG_REL_PARAM_ID, Consts::_AMP_EG_REL_PARAM_NAME,
        NormalisableRange<float>(0.01f, 20.0f, 0.01f, getSkewFactor(0.01f, 20.0f, 1.0f), false),
        Consts::_AMP_EG_REL_DEFAULT_VAL
    );
    params.push_back(std::move(ampEgRel));

    // PHASOR EG

    auto phasorEgAtk = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_EG_ATK_PARAM_ID, Consts::_PHASOR_EG_ATK_PARAM_NAME,
        NormalisableRange<float>(0.01f, 10.0f, 0.01f, getSkewFactor(0.01f, 10.0f, 1.0f), false),
        Consts::_PHASOR_EG_ATK_DEFAULT_VAL
    );
    params.push_back(std::move(phasorEgAtk));

    auto phasorEgDec = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_EG_DEC_PARAM_ID, Consts::_PHASOR_EG_DEC_PARAM_NAME,
        NormalisableRange<float>(0.01f, 2.0f, 0.01f, getSkewFactor(0.01f, 2.0f, 0.5f), false),
        Consts::_PHASOR_EG_DEC_DEFAULT_VAL
    );
    params.push_back(std::move(phasorEgDec));

    auto phasorEgSus = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_EG_SUS_PARAM_ID, Consts::_PHASOR_EG_SUS_PARAM_NAME,
        NormalisableRange<float>(-60.0f, 0.0f, 0.1f, getSkewFactor(-60.0f, 0.0f, -30.0f), false),
        Consts::_PHASOR_EG_SUS_DEFAULT_VAL
    );
    params.push_back(std::move(phasorEgSus));

    auto phasorEgRel = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_EG_REL_PARAM_ID, Consts::_PHASOR_EG_REL_PARAM_NAME,
        NormalisableRange<float>(0.01f, 20.0f, 0.01f, getSkewFactor(0.01f, 20.0f, 1.0f), false),
        Consts::_PHASOR_EG_REL_DEFAULT_VAL
    );
    params.push_back(std::move(phasorEgRel));

    // FILTER EG 

    auto filterEgAtk = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_EG_ATK_PARAM_ID, Consts::_FLTR_EG_ATK_PARAM_NAME,
        NormalisableRange<float>(0.01f, 10.0f, 0.01f, getSkewFactor(0.01f, 10.0f, 1.0f), false),
        Consts::_FLTR_EG_ATK_DEFAULT_VAL
    );
    params.push_back(std::move(filterEgAtk));

    auto filterEgDec = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_EG_DEC_PARAM_ID, Consts::_FLTR_EG_DEC_PARAM_NAME,
        NormalisableRange<float>(0.01f, 2.0f, 0.01f, getSkewFactor(0.01f, 2.0f, 0.5f), false),
        Consts::_FLTR_EG_DEC_DEFAULT_VAL
    );
    params.push_back(std::move(filterEgDec));

    auto filterEgSus = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_EG_SUS_PARAM_ID, Consts::_FLTR_EG_SUS_PARAM_NAME,
        NormalisableRange<float>(-60.0f, 0.0f, 0.1f, getSkewFactor(-60.0f, 0.0f, -30.0f), false),
        Consts::_FLTR_EG_SUS_DEFAULT_VAL
    );
    params.push_back(std::move(filterEgSus));

    auto filterEgRel = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_EG_REL_PARAM_ID, Consts::_FLTR_EG_REL_PARAM_NAME,
        NormalisableRange<float>(0.01f, 20.0f, 0.01f, getSkewFactor(0.01f, 20.0f, 1.0f), false),
        Consts::_FLTR_EG_REL_DEFAULT_VAL
    );
    params.push_back(std::move(filterEgRel));

    // MOD EG 

    auto modEgAtk = std::make_unique<AudioParameterFloat>(
        Consts::_MOD_EG_ATK_PARAM_ID, Consts::_MOD_EG_ATK_PARAM_NAME,
        NormalisableRange<float>(0.01f, 10.0f, 0.01f, getSkewFactor(0.01f, 10.0f, 1.0f), false),
        Consts::_MOD_EG_ATK_DEFAULT_VAL
    );
    params.push_back(std::move(modEgAtk));

    auto modEgDec = std::make_unique<AudioParameterFloat>(
        Consts::_MOD_EG_DEC_PARAM_ID, Consts::_MOD_EG_DEC_PARAM_NAME,
        NormalisableRange<float>(0.01f, 2.0f, 0.01f, getSkewFactor(0.01f, 2.0f, 0.5f), false),
        Consts::_MOD_EG_DEC_DEFAULT_VAL
    );
    params.push_back(std::move(modEgDec));

    auto modEgSus = std::make_unique<AudioParameterFloat>(
        Consts::_MOD_EG_SUS_PARAM_ID, Consts::_MOD_EG_SUS_PARAM_NAME,
        NormalisableRange<float>(-60.0f, 0.0f, 0.1f, getSkewFactor(-60.0f, 0.0f, -30.0f), false),
        Consts::_MOD_EG_SUS_DEFAULT_VAL
    );
    params.push_back(std::move(modEgSus));

    auto modEgRel = std::make_unique<AudioParameterFloat>(
        Consts::_MOD_EG_REL_PARAM_ID, Consts::_MOD_EG_REL_PARAM_NAME,
        NormalisableRange<float>(0.01f, 20.0f, 0.01f, getSkewFactor(0.01f, 20.0f, 1.0f), false),
        Consts::_MOD_EG_REL_DEFAULT_VAL
    );
    params.push_back(std::move(modEgRel));

    // LFOs

    auto lfoRate = std::make_unique<AudioParameterFloat>(
        Consts::_LFO_RATE_PARAM_ID, Consts::_LFO_RATE_PARAM_NAME,
        NormalisableRange<float>(0.1f, 100.0f, 0.01f, getSkewFactor(0.1f, 100.0f, 20.0f), false),
        Consts::_LFO_RATE_DEFAULT_VAL
    );
    params.push_back(std::move(lfoRate));

    auto lfoShape = std::make_unique<AudioParameterFloat>(
        Consts::_LFO_SHAPE_PARAM_ID, Consts::_LFO_SHAPE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 4.0f, 1.0f),
        Consts::_LFO_SHAPE_DEFAULT_VAL
    );
    params.push_back(std::move(lfoShape));

    // OSCILLATORs

    // OSC 01

    auto osc01Range = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_RANGE_PARAM_ID, Consts::_OSC_01_RANGE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 3.0f, 1.0f),
        Consts::_OSC_01_RANGE_DEFAULT_VAL
    );
    params.push_back(std::move(osc01Range));

    auto osc01CoarseTune = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_COARSE_TUNE_PARAM_ID, Consts::_OSC_01_COARSE_TUNE_PARAM_NAME,
        NormalisableRange<float>(-12.0f, 12.0f, 0.1f),
        Consts::_OSC_01_COARSE_TUNE_DEFAULT_VAL
    );
    params.push_back(std::move(osc01CoarseTune));

    auto osc01FineTune = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_FINE_TUNE_PARAM_ID, Consts::_OSC_01_FINE_TUNE_PARAM_NAME,
        NormalisableRange<float>(-100.0f, 100.0f, 0.1f),
        Consts::_OSC_01_FINE_TUNE_DEFAULT_VAL
    );
    params.push_back(std::move(osc01FineTune));

    auto osc01ModDepth = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_MOD_DEPTH_PARAM_ID, Consts::_OSC_01_MOD_DEPTH_PARAM_NAME,
        NormalisableRange<float>(-1.0f, 1.0f, 0.01f),
        Consts::_OSC_01_MOD_DEPTH_DEFAULT_VAL
    );
    params.push_back(std::move(osc01ModDepth));

    auto osc01ModMode = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_MOD_MODE_PARAM_ID, Consts::_OSC_01_MOD_MODE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_OSC_01_MOD_MODE_DEFAULT_VAL
    );
    params.push_back(std::move(osc01ModMode));

    auto osc01ShapeInt = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_SHAPE_INT_PARAM_ID, Consts::_OSC_01_SHAPE_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_OSC_01_SHAPE_INT_DEFAULT_VAL
    );
    params.push_back(std::move(osc01ShapeInt));

    // OSC 02

    auto osc02Range = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_RANGE_PARAM_ID, Consts::_OSC_02_RANGE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 3.0f, 1.0f),
        Consts::_OSC_02_RANGE_DEFAULT_VAL
    );
    params.push_back(std::move(osc02Range));

    auto osc02CoarseTune = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_COARSE_TUNE_PARAM_ID, Consts::_OSC_02_COARSE_TUNE_PARAM_NAME,
        NormalisableRange<float>(-12.0f, 12.0f, 0.1f),
        Consts::_OSC_02_COARSE_TUNE_DEFAULT_VAL
    );
    params.push_back(std::move(osc02CoarseTune));

    auto osc02FineTune = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_FINE_TUNE_PARAM_ID, Consts::_OSC_02_FINE_TUNE_PARAM_NAME,
        NormalisableRange<float>(-100.0f, 100.0f, 0.1f),
        Consts::_OSC_02_FINE_TUNE_DEFAULT_VAL
    );
    params.push_back(std::move(osc02FineTune));

    auto osc02ModDepth = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_MOD_DEPTH_PARAM_ID, Consts::_OSC_02_MOD_DEPTH_PARAM_NAME,
        NormalisableRange<float>(-1.0f, 1.0f, 0.01f),
        Consts::_OSC_02_MOD_DEPTH_DEFAULT_VAL
    );
    params.push_back(std::move(osc02ModDepth));

    auto osc02ModMode = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_MOD_MODE_PARAM_ID, Consts::_OSC_02_MOD_MODE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_OSC_02_MOD_MODE_DEFAULT_VAL
    );
    params.push_back(std::move(osc02ModMode));

    auto osc02ShapeInt = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_SHAPE_INT_PARAM_ID, Consts::_OSC_02_SHAPE_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_OSC_02_SHAPE_INT_DEFAULT_VAL
    );
    params.push_back(std::move(osc02ShapeInt));

    // PHASORs

    // PHASOR 01

    auto phasor01Shape = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_01_SHAPE_PARAM_ID, Consts::_PHASOR_01_SHAPE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_PHASOR_01_SHAPE_DEFAULT_VAL
    );
    params.push_back(std::move(phasor01Shape));

    auto phasor01EgInt = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_01_EG_INT_PARAM_ID, Consts::_PHASOR_01_EG_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_PHASOR_01_EG_INT_DEFAULT_VAL
    );
    params.push_back(std::move(phasor01EgInt));

    auto phasor01LfoInt = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_01_LFO_INT_PARAM_ID, Consts::_PHASOR_01_LFO_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_PHASOR_01_LFO_INT_DEFAULT_VAL
    );
    params.push_back(std::move(phasor01LfoInt));

    // PHASOR 02

    auto phasor02Shape = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_02_SHAPE_PARAM_ID, Consts::_PHASOR_02_SHAPE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_PHASOR_02_SHAPE_DEFAULT_VAL
    );
    params.push_back(std::move(phasor02Shape));

    auto phasor02EgInt = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_02_EG_INT_PARAM_ID, Consts::_PHASOR_02_EG_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_PHASOR_02_EG_INT_DEFAULT_VAL
    );
    params.push_back(std::move(phasor02EgInt));

    auto phasor02LfoInt = std::make_unique<AudioParameterFloat>(
        Consts::_PHASOR_02_LFO_INT_PARAM_ID, Consts::_PHASOR_02_LFO_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_PHASOR_02_LFO_INT_DEFAULT_VAL
    );
    params.push_back(std::move(phasor02LfoInt));

    // FILTER

    auto filterCutoff = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_CUTOFF_PARAM_ID, Consts::_FLTR_CUTOFF_PARAM_NAME,
        NormalisableRange<float>(20.0f, 20000.0f, 0.1f, getSkewFactor(20.0f, 20000.0f, 2000.0f), false),
        Consts::_FLTR_CUTOFF_DEFAULT_VAL
    );
    params.push_back(std::move(filterCutoff));

    auto filterReso = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_RESO_PARAM_ID, Consts::_FLTR_RESO_PARAM_NAME,
        NormalisableRange<float>(0.1f, 8.4, 0.01f, getSkewFactor(0.1f, 8.4f, 1.4f), false),
        Consts::_FLTR_RESO_DEFAULT_VAL
    );
    params.push_back(std::move(filterReso));

    auto filterDrive = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_DRIVE_PARAM_ID, Consts::_FLTR_DRIVE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_FLTR_DRIVE_DEFAULT_VAL
    );
    params.push_back(std::move(filterDrive));

    auto filterEgModDepth = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_EG_MOD_DEPTH_PARAM_ID, Consts::_FLTR_EG_MOD_DEPTH_PARAM_NAME,
        NormalisableRange<float>(-1.0f, 1.0f, 0.01f),
        Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL
    );
    params.push_back(std::move(filterEgModDepth));

    auto filterLfoModDepth = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_LFO_MOD_DEPTH_PARAM_ID, Consts::_FLTR_LFO_MOD_DEPTH_PARAM_NAME,
        NormalisableRange<float>(-1.0f, 1.0f, 0.01f),
        Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL
    );
    params.push_back(std::move(filterLfoModDepth));

    // AMP

    auto level = std::make_unique<AudioParameterFloat>(
        Consts::_LEVEL_PARAM_ID, Consts::_LEVEL_PARAM_NAME,
        NormalisableRange<float>(-30.0f, 6.0f, 0.1f, getSkewFactor(-30.0f, 6.0f, 0.0f), false),
        Consts::_LEVEL_DEFAULT_VAL
    );
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
float PhantomAudioProcessor::getSkewFactor(float start, float end, float center)
{
    return std::log((0.5f)) / std::log((center - start) / (end - start));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhantomAudioProcessor();
}
