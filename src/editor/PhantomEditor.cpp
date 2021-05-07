/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"

#include "../utils/PhantomUtils.h"

PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts) : AudioProcessorEditor(&p), m_processor(p), m_parameters(vts)
{
    m_phantomAmplifier = std::make_unique<PhantomAmplifierComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomAmplifier.get());

    m_phantomOscillators = std::make_unique<PhantomOscillatorComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomOscillators.get());

    m_phantomPhasors = std::make_unique<PhantomPhasorComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomPhasors.get());

    m_phantomMixer = std::make_unique<PhantomMixerComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomMixer.get());

    m_phantomFilter = std::make_unique<PhantomFilterComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomFilter.get());

    m_phantomLFOs = std::make_unique<PhantomLFOComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomLFOs.get());

    m_phantomEnvelopes = std::make_unique<PhantomEnvelopeComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomEnvelopes.get());

    m_phantomAnalyzer = std::make_unique<PhantomAnalyzerComponent>(m_lookAndFeel);
    addAndMakeVisible(m_phantomAnalyzer.get());

    m_phantomOscilloscope = std::make_unique<PhantomOscilloscopeComponent>(m_lookAndFeel);
    addAndMakeVisible(m_phantomOscilloscope.get());

    m_phantomPreset = std::make_unique<PhantomPresetComponent>(m_lookAndFeel, m_processor.getPresetManager());
    addAndMakeVisible(m_phantomPreset.get());

    init();
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    setLookAndFeel(nullptr);

    m_phantomAmplifier = nullptr;
    m_phantomOscillators = nullptr;
    m_phantomPhasors = nullptr;
    m_phantomMixer = nullptr;
    m_phantomFilter = nullptr;
    m_phantomLFOs = nullptr;
    m_phantomEnvelopes = nullptr;
    m_phantomPreset = nullptr;
    m_phantomAnalyzer = nullptr;
    m_phantomOscilloscope = nullptr;
}

void PhantomAudioProcessorEditor::init()
{
    setLookAndFeel(&m_lookAndFeel);

    float ratio = 16.0f / 9.0f;
    setResizable(true, true);
    setResizeLimits(720 * ratio, 720, 1280 * ratio, 1280);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(720 * ratio, 720);
}

void PhantomAudioProcessorEditor::reset()
{
    m_phantomAmplifier->reset();
    m_phantomOscillators->reset();
    m_phantomPhasors->reset();
    m_phantomMixer->reset();
    m_phantomFilter->reset();
    m_phantomLFOs->reset();
    m_phantomEnvelopes->reset();
}

void PhantomAudioProcessorEditor::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomAudioProcessorEditor::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    const int margin = canvas.getWidth() / 60;
    canvas.removeFromTop(margin);
    canvas.removeFromRight(margin);
    canvas.removeFromBottom(margin);
    canvas.removeFromLeft(margin);

    const int width = canvas.getWidth();
    const int height = canvas.getHeight();
    const int sectionHeight = (height - (margin * 6)) / 4;

    // TOP
    const int topKnobWidth = (width - margin) / 7;
    Rectangle<int> topArea = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    m_phantomAmplifier->update(margin, topKnobWidth, topArea.removeFromLeft(topKnobWidth));
    topArea.removeFromLeft(margin);
    m_phantomOscillators->update(margin, topKnobWidth, topArea);

    // MIDDLE TOP
    const int middleTopKnobWidth = (width - (margin * 2)) / 7;
    Rectangle<int> middleTopArea = canvas.removeFromTop(sectionHeight + (margin * 2));
    canvas.removeFromTop(margin);

    Rectangle<int> analyzerArea = middleTopArea.removeFromLeft(middleTopKnobWidth * 2);
    m_phantomAnalyzer->update(analyzerArea);
    middleTopArea.removeFromLeft(margin);

    Rectangle<int> phasorArea = middleTopArea.removeFromLeft(middleTopKnobWidth * 3);
    middleTopArea.removeFromLeft(margin);

    Rectangle<int> presetArea = phasorArea.removeFromBottom(margin * 1.5);
    m_phantomPreset->update(presetArea);

    phasorArea.removeFromBottom(margin * 0.5);
    m_phantomPhasors->update(margin, middleTopKnobWidth, phasorArea);

    Rectangle<int> oscilloscopeArea = middleTopArea;
    m_phantomOscilloscope->update(oscilloscopeArea);

    // MIDDLE BOTTOM
    const int middleBottomKnobWidth = (width - (margin * 2)) / 7;
    Rectangle<int> middleBottomArea = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    Rectangle<int> mixerArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 2);
    m_phantomMixer->update(margin, middleBottomKnobWidth, mixerArea);
    middleBottomArea.removeFromLeft(margin);

    Rectangle<int> filterArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 3);
    m_phantomFilter->update(margin, middleBottomKnobWidth, filterArea);
    middleBottomArea.removeFromLeft(margin);

    Rectangle<int> lfoArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 2);
    m_phantomLFOs->update(margin, middleBottomKnobWidth, lfoArea);

    // BOTTOM
    const int bottomKnobWidth = (width - (margin * 2)) / 8;
    Rectangle<int> envelopeArea = canvas;
    m_phantomEnvelopes->update(margin, bottomKnobWidth, envelopeArea);
}
