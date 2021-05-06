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
    m_phantomAmplifier = std::make_unique<PhantomAmplifierComponent>(vts);
    addAndMakeVisible(m_phantomAmplifier.get());

    m_phantomOscillators = std::make_unique<PhantomOscillatorComponent>(vts);
    addAndMakeVisible(m_phantomOscillators.get());

    m_phantomPhasors = std::make_unique<PhantomPhasorComponent>(vts);
    addAndMakeVisible(m_phantomPhasors.get());

    m_phantomMixer = std::make_unique<PhantomMixerComponent>(vts);
    addAndMakeVisible(m_phantomMixer.get());

    m_phantomFilter = std::make_unique<PhantomFilterComponent>(vts);
    addAndMakeVisible(m_phantomFilter.get());

    m_phantomLFOs = std::make_unique<PhantomLFOComponent>(vts);
    addAndMakeVisible(m_phantomLFOs.get());

    m_phantomEnvelopes = std::make_unique<PhantomEnvelopeComponent>(vts);
    addAndMakeVisible(m_phantomEnvelopes.get());

    m_phantomAnalyzer = std::make_unique<PhantomAnalyzerComponent>();
    addAndMakeVisible(m_phantomAnalyzer.get());

    m_phantomOscilloscope = std::make_unique<PhantomOscilloscopeComponent>();
    addAndMakeVisible(m_phantomOscilloscope.get());

    initPresetMenu();

    loadPresetFilePaths();

    initEditor();
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

    m_phantomAnalyzer = nullptr;
    m_phantomOscilloscope = nullptr;
}

void PhantomAudioProcessorEditor::initPresetMenu()
{
    m_presetLabel.setText("PRESET: ", dontSendNotification);
    m_presetLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&m_presetLabel);

    m_presetButton.setButtonText(m_processor.m_presetName);
    m_presetButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetButton.setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(&m_presetButton);
    m_presetButton.onClick = [this](){
        PopupMenu menu;

        menu.addItem(PopupMenu::Item("Copy to clipboard")
            .setAction([this](){
                SystemClipboard::copyTextToClipboard(*m_processor.saveStateToText());
            })
        );
        menu.addItem(PopupMenu::Item("Paste from clipboard")
            .setAction([this](){
                m_processor.loadStateFromText(SystemClipboard::getTextFromClipboard());

                resetGui();
            })
        );

        menu.addSeparator();

        menu.addItem(PopupMenu::Item("Initialize")
            .setAction([this](){
                m_processor.resetState();
                
                resetParameters();
                resetGui();
            })
        );
        menu.addItem(PopupMenu::Item("Save as")
            .setAction([this](){
                String presetDirPath = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
                    + "/Black Box DSP/Phantom/Presets";
                FileChooser browser("Save as ...", presetDirPath, "*.xml");

                if(browser.browseForFileToSave(true))
                {
                    File res = browser.getResult();
                    m_processor.saveStateToFile(res);

                    loadPresetFilePaths();
                    setPresetIdx();
                    resetGui();
                }
            })
        );

        menu.addSeparator();

        menu.addSectionHeader("Presets");

        addPresetsToMenu(menu);

        menu.showMenu(PopupMenu::Options().withParentComponent(this));
    };

    m_presetLeftButton.setButtonText("<");
    m_presetLeftButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetLeftButton.setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(&m_presetLeftButton);
    m_presetLeftButton.onClick = [this](){
        m_presetIdx--;
        loadPresetFileAtIndex();
    };

    m_presetRightButton.setButtonText(">");
    m_presetRightButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetRightButton.setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(&m_presetRightButton);
    m_presetRightButton.onClick = [this](){
        m_presetIdx++;
        loadPresetFileAtIndex();
    };
}

void PhantomAudioProcessorEditor::initEditor()
{
    setLookAndFeel(&m_lookAndFeel);

    float ratio = 16.0f / 9.0f;
    setResizable(true, true);
    setResizeLimits(720 * ratio, 720, 1280 * ratio, 1280);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(720 * ratio, 720);
}

void PhantomAudioProcessorEditor::addPresetsToMenu(PopupMenu& menu)
{
    String previousTypeDir = String("");
    PopupMenu typeDirSubMenu;

    for(File pf : m_processor.getPresetFiles())
    {
        if(previousTypeDir.isEmpty())
            previousTypeDir = pf.getParentDirectory().getFileName();
        
        String typeDir = String(pf.getParentDirectory().getFileName());
        if(!previousTypeDir.equalsIgnoreCase(typeDir))
        {
            menu.addSubMenu(previousTypeDir, typeDirSubMenu);
            typeDirSubMenu.clear();
        }

        previousTypeDir = String(typeDir);

        String presetName = String(pf.getFileNameWithoutExtension());
        typeDirSubMenu.addItem(
            PopupMenu::Item(presetName)
            .setEnabled(!presetName.equalsIgnoreCase(m_processor.m_presetName))
            .setAction([this, pf](){
                File presetFile = File(pf.getFullPathName());
                m_processor.loadStateFromFile(presetFile);

                setPresetIdx();
                resetGui();
            })
        );
    }

    menu.addSubMenu(previousTypeDir, typeDirSubMenu);
}


void PhantomAudioProcessorEditor::loadPresetFilePaths()
{
    m_presetFilePaths.clearQuick();

    for(File pf : m_processor.getPresetFiles())
        m_presetFilePaths.add(pf.getFullPathName());
}

void PhantomAudioProcessorEditor::loadPresetFileAtIndex()
{

    if(m_presetIdx >= -4 && m_presetIdx <= -2)
    {
        int previousIdx = m_presetIdx;

        if(!setPresetIdx())
            m_presetIdx = 0;
        else 
            if(previousIdx == -4)
                m_presetIdx--;
            else
                m_presetIdx++;
    }

    if(m_presetIdx < 0)
        m_presetIdx = m_presetFilePaths.size() - 1;
    else if(m_presetIdx >= m_presetFilePaths.size())
        m_presetIdx = 0;

    File file = File(m_presetFilePaths[m_presetIdx]);
    m_processor.loadStateFromFile(file);

    resetGui();
}

bool PhantomAudioProcessorEditor::setPresetIdx()
{
    int count = 0;

    for(File pf : m_processor.getPresetFiles())
    {
        String presetName = pf.getFileNameWithoutExtension();
        if(presetName == m_processor.m_presetName)
        {
            m_presetIdx = count;

            return true;
        }

        count++;
    }

    return false;
}

void PhantomAudioProcessorEditor::resetGui()
{
    m_presetButton.setButtonText(m_processor.m_presetName);
}

void PhantomAudioProcessorEditor::resetParameters()
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
    resetGui();

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
    const int presetAreaWidth = presetArea.getWidth();
    m_presetLabel.setBounds(presetArea.removeFromLeft(presetAreaWidth * 0.3));
    m_presetButton.setBounds(presetArea.removeFromLeft(presetAreaWidth * 0.4));
    presetArea.removeFromLeft(presetAreaWidth * 0.1);
    m_presetLeftButton.setBounds(presetArea.removeFromLeft(presetAreaWidth * 0.1));
    m_presetRightButton.setBounds(presetArea);
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
