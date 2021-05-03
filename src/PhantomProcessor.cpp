/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#include "PhantomData.h"
#include "PhantomEditor.h"
#include "PhantomProcessor.h"

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
    m_synth.reset(new PhantomSynth(m_parameters));
    m_amp.reset(new PhantomAmplifier(m_parameters));

    writePresetFiles();
}

PhantomAudioProcessor::~PhantomAudioProcessor()
{
    m_synth = nullptr;
    m_amp = nullptr;
}

AudioProcessorValueTreeState::ParameterLayout PhantomAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    // AMP

    auto level = std::make_unique<AudioParameterFloat>(
        Consts::_LEVEL_PARAM_ID, Consts::_LEVEL_PARAM_NAME,
        NormalisableRange<float>(-30.0f, 6.0f, 0.1f, getSkewFactor(-30.0f, 6.0f, 0.0f), false),
        Consts::_LEVEL_DEFAULT_VAL
    );
    params.push_back(std::move(level));

    // OSCILLATORs

    auto oscSync = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_SYNC_PARAM_ID, Consts::_OSC_SYNC_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_OSC_SYNC_DEFAULT_VAL
    );
    params.push_back(std::move(oscSync));

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

    auto osc01ShapeInt = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_SHAPE_INT_PARAM_ID, Consts::_OSC_01_SHAPE_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_OSC_01_SHAPE_INT_DEFAULT_VAL
    );
    params.push_back(std::move(osc01ShapeInt));

    auto osc01ModDepth = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_MOD_DEPTH_PARAM_ID, Consts::_OSC_01_MOD_DEPTH_PARAM_NAME,
        NormalisableRange<float>(-1.0f, 1.0f, 0.01f),
        Consts::_OSC_01_MOD_DEPTH_DEFAULT_VAL
    );
    params.push_back(std::move(osc01ModDepth));

    auto osc01ModSource = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_01_MOD_SOURCE_PARAM_ID, Consts::_OSC_01_MOD_SOURCE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_OSC_01_MOD_SOURCE_DEFAULT_VAL
    );
    params.push_back(std::move(osc01ModSource));

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

    auto osc02ShapeInt = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_SHAPE_INT_PARAM_ID, Consts::_OSC_02_SHAPE_INT_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_OSC_02_SHAPE_INT_DEFAULT_VAL
    );
    params.push_back(std::move(osc02ShapeInt));

    auto osc02ModDepth = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_MOD_DEPTH_PARAM_ID, Consts::_OSC_02_MOD_DEPTH_PARAM_NAME,
        NormalisableRange<float>(-1.0f, 1.0f, 0.01f),
        Consts::_OSC_02_MOD_DEPTH_DEFAULT_VAL
    );
    params.push_back(std::move(osc02ModDepth));

    auto osc02ModSource = std::make_unique<AudioParameterFloat>(
        Consts::_OSC_02_MOD_SOURCE_PARAM_ID, Consts::_OSC_02_MOD_SOURCE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        Consts::_OSC_02_MOD_SOURCE_DEFAULT_VAL
    );
    params.push_back(std::move(osc02ModSource));

    // PHASORs

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

    // MIXER    

    auto mixerOscBalance = std::make_unique<AudioParameterFloat>(
        Consts::_MIXER_OSC_BAL_PARAM_ID, Consts::_MIXER_OSC_BAL_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_MIXER_OSC_BAL_DEFAULT_VAL
    );
    params.push_back(std::move(mixerOscBalance));

    auto mixerAmpGain = std::make_unique<AudioParameterFloat>(
        Consts::_MIXER_AMP_GAIN_PARAM_ID, Consts::_MIXER_AMP_GAIN_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.2f, 0.01f),
        Consts::_MIXER_AMP_GAIN_DEFAULT_VAL
    );
    params.push_back(std::move(mixerAmpGain));

    auto mixerRingMod = std::make_unique<AudioParameterFloat>(
        Consts::_MIXER_RING_MOD_PARAM_ID, Consts::_MIXER_RING_MOD_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_MIXER_RING_MOD_DEFAULT_VAL
    );
    params.push_back(std::move(mixerRingMod));

    auto mixerNoise = std::make_unique<AudioParameterFloat>(
        Consts::_MIXER_NOISE_PARAM_ID, Consts::_MIXER_NOISE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        Consts::_MIXER_NOISE_DEFAULT_VAL
    );
    params.push_back(std::move(mixerNoise));

    // FILTER

    auto filterMode = std::make_unique<AudioParameterFloat>(
        Consts::_FLTR_MODE_PARAM_ID, Consts::_FLTR_MODE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 2.0f, 1.0f),
        Consts::_FLTR_MODE_DEFAULT_VAL
    );
    params.push_back(std::move(filterMode));

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

    // LFOs

    auto lfo01Rate = std::make_unique<AudioParameterFloat>(
        Consts::_LFO_01_RATE_PARAM_ID, Consts::_LFO_01_RATE_PARAM_NAME,
        NormalisableRange<float>(0.1f, 100.0f, 0.01f, getSkewFactor(0.1f, 100.0f, 20.0f), false),
        Consts::_LFO_01_RATE_DEFAULT_VAL
    );
    params.push_back(std::move(lfo01Rate));

    auto lfo01Shape = std::make_unique<AudioParameterFloat>(
        Consts::_LFO_01_SHAPE_PARAM_ID, Consts::_LFO_01_SHAPE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 4.0f, 1.0f),
        Consts::_LFO_01_SHAPE_DEFAULT_VAL
    );
    params.push_back(std::move(lfo01Shape));

    auto lfo02Rate = std::make_unique<AudioParameterFloat>(
        Consts::_LFO_02_RATE_PARAM_ID, Consts::_LFO_02_RATE_PARAM_NAME,
        NormalisableRange<float>(0.1f, 100.0f, 0.01f, getSkewFactor(0.1f, 100.0f, 20.0f), false),
        Consts::_LFO_02_RATE_DEFAULT_VAL
    );
    params.push_back(std::move(lfo02Rate));

    auto lfo02Shape = std::make_unique<AudioParameterFloat>(
        Consts::_LFO_02_SHAPE_PARAM_ID, Consts::_LFO_02_SHAPE_PARAM_NAME,
        NormalisableRange<float>(0.0f, 4.0f, 1.0f),
        Consts::_LFO_02_SHAPE_DEFAULT_VAL
    );
    params.push_back(std::move(lfo02Shape));

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

    return { params.begin(), params.end() };
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
    ignoreUnused(samplesPerBlock);

    int numChannels = jmin(getMainBusNumInputChannels(), getMainBusNumOutputChannels());
    m_synth->init((float) sampleRate, samplesPerBlock, numChannels);
    
    PhantomAudioProcessorEditor* editor = static_cast<PhantomAudioProcessorEditor*>(getActiveEditor());
    if(editor)
        editor->m_oscilloscope->init((float) sampleRate, samplesPerBlock);
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
        editor->m_oscilloscope->pushBuffer(buffer);
        editor->m_analyzer->pushBuffer(buffer);
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
    xml = saveMetadataToXml(std::move(xml));
    copyXmlToBinary(*xml, destData);
}

void PhantomAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if(xml.get() != nullptr)
        loadStateFromXml(std::move(xml));
}

std::unique_ptr<XmlElement> PhantomAudioProcessor::loadStateFromXml(std::unique_ptr<XmlElement> xml)
{
    if(xml->hasTagName(Consts::_PLUGIN_NAME))
    {
        bool doPluginVersionsMatch = String(Consts::_PLUGIN_VERSION).equalsIgnoreCase(xml->getStringAttribute("pluginVersion"));
        jassert(doPluginVersionsMatch);

        String presetName = String(xml->getStringAttribute("presetName"));
        if(presetName.isEmpty() || presetName.equalsIgnoreCase("Init"))
            if(m_presetName.isEmpty())
                m_presetName = String("Init");
            else
                // WARNING: Preset has already been loaded and plugin is called to load either the same
                // or another XMl data object.
                return xml;
        else
            m_presetName = presetName;

        m_parameters.replaceState(ValueTree::fromXml(*xml));
    }

    return xml;
}

std::unique_ptr<XmlElement> PhantomAudioProcessor::saveMetadataToXml(std::unique_ptr<XmlElement> xml)
{
    return saveMetadataToXml(std::move(xml), m_presetName);
}

std::unique_ptr<XmlElement> PhantomAudioProcessor::saveMetadataToXml(std::unique_ptr<XmlElement> xml, String& presetName)
{
    xml->setAttribute("pluginVersion", Consts::_PLUGIN_VERSION);
    xml->setAttribute("presetName", presetName);

    return xml;
}


std::unique_ptr<String> PhantomAudioProcessor::saveStateToText()
{
    std::unique_ptr<XmlElement> xml(m_parameters.state.createXml());
    
    return std::make_unique<String>(saveMetadataToXml(std::move(xml))->toString());
}

void PhantomAudioProcessor::loadStateFromText(const String& stateStr)
{
    std::unique_ptr<XmlElement> xml = juce::parseXML(stateStr);
    if(xml)
        loadStateFromXml(std::move(xml));
}

bool PhantomAudioProcessor::saveStateToFile(File& file) 
{
    std::unique_ptr<XmlElement> xml(m_parameters.state.createXml());

    m_presetName = file.getFileNameWithoutExtension();

    return saveMetadataToXml(std::move(xml))->writeTo(file);
}

bool PhantomAudioProcessor::saveXmlToFile(std::unique_ptr<XmlElement> xml, File& dir)
{
    // The file must be stored within a direcctory!
    jassert(dir.isDirectory());

    String presetType = xml->getStringAttribute("presetType");
    String presetName = xml->getStringAttribute("presetName");

    xml->removeAttribute("presetType");

    // These attributes must exist!
    jassert(presetType.isNotEmpty() && presetName.isNotEmpty());

    File typeSubDir = File(dir.getFullPathName() + "/" + presetType);
    if(!typeSubDir.exists())
        typeSubDir.createDirectory();

    File presetFile = File(typeSubDir.getFullPathName() + "/" + presetName + ".xml");

    return saveMetadataToXml(std::move(xml), presetName)->writeTo(presetFile);
}

void PhantomAudioProcessor::loadStateFromFile(File& file)
{
    std::unique_ptr<XmlElement> xml = juce::parseXML(file);
    if(xml && xml->hasTagName(Consts::_PLUGIN_NAME))
        loadStateFromXml(std::move(xml));
}

File PhantomAudioProcessor::getPresetDirectory()
{
    String presetDirPath = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
        + "/Black Box DSP/Phantom/Presets";

    return File(presetDirPath);
}

Array<File> PhantomAudioProcessor::getPresetFiles()
{
    return getPresetDirectory().findChildFiles(File::findFiles, true, "*.xml");
}

void PhantomAudioProcessor::writePresetFiles()
{
    File presetDir = getPresetDirectory();

    if(presetDir.exists())
        return;

    presetDir.createDirectory();

    saveXmlToFile(juce::parseXML(PhantomData::algo_xml), presetDir);
    saveXmlToFile(juce::parseXML(PhantomData::analog_xml), presetDir);
    saveXmlToFile(juce::parseXML(PhantomData::feather_xml), presetDir);
    saveXmlToFile(juce::parseXML(PhantomData::noisetap_xml), presetDir);
    saveXmlToFile(juce::parseXML(PhantomData::overlord_xml), presetDir);
    saveXmlToFile(juce::parseXML(PhantomData::siren_xml), presetDir);
    saveXmlToFile(juce::parseXML(PhantomData::thestack_xml), presetDir);
}

void PhantomAudioProcessor::resetState()
{
    m_presetName = String("Init");
}

float PhantomAudioProcessor::getSkewFactor(float start, float end, float center)
{
    return std::log(0.5f) / std::log((center - start) / (end - start));
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhantomAudioProcessor();
}
