/*
  ==============================================================================

    PhantomPreset.cpp
    Created: 06 May 2021 15:54:04
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomPreset.h"

#include "../editor/PhantomEditor.h"
#include "../utils/PhantomUtils.h"

PhantomPresetComponent::PhantomPresetComponent(PhantomLookAndFeel& plf, PhantomPresetManager& pm, AudioProcessorValueTreeState& vts) : IComponent(plf, vts), m_presetManager(pm)
{
    init();
}

PhantomPresetComponent::~PhantomPresetComponent()
{
    m_presetLabel = nullptr;
    m_presetButton = nullptr;

    m_presetLeftButton = nullptr;
    m_presetRightButton = nullptr;
}

void PhantomPresetComponent::init()
{
    m_presetLabel = std::make_unique<Label>();
    m_presetLabel->setText("PRESET: ", dontSendNotification);
    m_presetLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(m_presetLabel.get());

    m_presetButton = std::make_unique<TextButton>();
    m_presetButton->setButtonText(m_presetManager.getCurrentPresetName());
    m_presetButton->setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetButton->setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(m_presetButton.get());
    m_presetButton->onClick = [this](){
        PopupMenu menu;

        menu.addItem(PopupMenu::Item("Copy to clipboard")
            .setAction([this](){
                SystemClipboard::copyTextToClipboard(*m_presetManager.saveStateToText());
            })
        );
        menu.addItem(PopupMenu::Item("Paste from clipboard")
            .setAction([this](){
                m_presetManager.loadStateFromText(SystemClipboard::getTextFromClipboard());
            })
        );

        menu.addSeparator();

        menu.addItem(PopupMenu::Item("Initialize")
            .setAction([this](){
                m_presetManager.init();

                PhantomAudioProcessorEditor* editor = findParentComponentOfClass<PhantomAudioProcessorEditor>();
                editor->reset();           
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
                    m_presetManager.saveStateToFile(res);

                    m_presetManager.loadPresetFilePaths();
                    m_presetManager.setPresetIdx();
                }
            })
        );

        menu.addSeparator();

        menu.addSectionHeader("Presets");

        addPresetsToMenu(menu);

        PhantomAudioProcessorEditor* editor = findParentComponentOfClass<PhantomAudioProcessorEditor>();
        menu.showMenu(PopupMenu::Options().withParentComponent(editor));
    };

    m_presetLeftButton = std::make_unique<TextButton>();
    m_presetLeftButton->setButtonText("<");
    m_presetLeftButton->setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetLeftButton->setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(m_presetLeftButton.get());
    m_presetLeftButton->onClick = [this](){
        m_presetManager.loadPresetFile(false);
    };

    m_presetRightButton = std::make_unique<TextButton>();
    m_presetRightButton->setButtonText(">");
    m_presetRightButton->setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetRightButton->setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(m_presetRightButton.get());
    m_presetRightButton->onClick = [this](){
        m_presetManager.loadPresetFile(true);
    };
}

void PhantomPresetComponent::reset()
{
    m_presetButton->setButtonText(m_presetManager.getCurrentPresetName());
}

void PhantomPresetComponent::paint(Graphics& g)
{
    reset();

    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomPresetComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    const int width = getWidth();
    m_presetLabel->setBounds(canvas.removeFromLeft(width * 0.3));
    m_presetButton->setBounds(canvas.removeFromLeft(width * 0.4));

    canvas.removeFromLeft(width * 0.1);

    m_presetLeftButton->setBounds(canvas.removeFromLeft(width * 0.1));
    m_presetRightButton->setBounds(canvas);
}

void PhantomPresetComponent::addPresetsToMenu(PopupMenu& menu)
{
    String previousTypeDir = String("");
    PopupMenu typeDirSubMenu;

    for(File pf : m_presetManager.getPresetFiles())
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
            .setEnabled(!presetName.equalsIgnoreCase(m_presetManager.getCurrentPresetName()))
            .setAction([this, pf](){
                File presetFile = File(pf.getFullPathName());
                m_presetManager.loadStateFromFile(presetFile);
                m_presetManager.setPresetIdx();
            })
        );
    }

    menu.addSubMenu(previousTypeDir, typeDirSubMenu);
}
