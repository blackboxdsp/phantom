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
    m_presetButton = nullptr;

    m_presetLeftButton = nullptr;
    m_presetRightButton = nullptr;
}

void PhantomPresetComponent::init()
{
    m_presetButton = std::make_unique<TextButton>();
    m_presetButton->setLookAndFeel(&m_lookAndFeel);
    m_presetButton->setButtonText(m_presetManager.getCurrentPresetName());
    m_presetButton->setColour(TextButton::buttonColourId, Consts::_BLACK_COLOUR.withAlpha(k_idleButtonAlpha));
    m_presetButton->setColour(TextButton::buttonOnColourId, Consts::_BLACK_COLOUR.withAlpha(k_hoverButtonAlpha));
    m_presetButton->setColour(ComboBox::outlineColourId, Consts::_BLACK_COLOUR);
    m_presetButton->setColour(TextButton::textColourOnId, Consts::_SECONDARY_COLOUR);
    m_presetButton->setColour(TextButton::textColourOffId, Consts::_SECONDARY_COLOUR);
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
    m_presetLeftButton->setLookAndFeel(&m_lookAndFeel);
    m_presetLeftButton->setButtonText(" ");
    m_presetLeftButton->setColour(TextButton::buttonColourId, Consts::_BLACK_COLOUR.withAlpha(k_idleButtonAlpha));
    m_presetLeftButton->setColour(TextButton::buttonOnColourId, Consts::_BLACK_COLOUR.withAlpha(k_hoverButtonAlpha));
    m_presetLeftButton->setColour(ComboBox::outlineColourId, Consts::_BLACK_COLOUR);
    addAndMakeVisible(m_presetLeftButton.get());
    m_presetLeftButton->onClick = [this](){
        m_presetManager.loadPresetFile(false);
    };

    m_presetRightButton = std::make_unique<TextButton>();
    m_presetRightButton->setLookAndFeel(&m_lookAndFeel);
    m_presetRightButton->setButtonText(" ");
    m_presetRightButton->setColour(TextButton::buttonColourId, Consts::_BLACK_COLOUR.withAlpha(k_idleButtonAlpha));
    m_presetRightButton->setColour(TextButton::buttonOnColourId, Consts::_BLACK_COLOUR.withAlpha(k_hoverButtonAlpha));
    m_presetRightButton->setColour(ComboBox::outlineColourId, Consts::_BLACK_COLOUR);
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
}

void PhantomPresetComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    canvas.removeFromBottom(m_margin * 0.4f);

    int width = getWidth();

    canvas.removeFromLeft(width * 0.25f);
    canvas.removeFromRight(width * 0.25f);

    width = canvas.getWidth();

    canvas.removeFromLeft(width * 0.3f);

    Rectangle<int> presetNavArea = canvas.removeFromRight(width * 0.3f);
    m_presetRightButton->setBounds(presetNavArea.removeFromRight(m_margin * 1.75f));
    presetNavArea.removeFromRight(m_margin * 1.3f);
    m_presetLeftButton->setBounds(presetNavArea.removeFromRight(m_margin * 1.75f));

    canvas.expand(m_margin * 0.25f, 0);
    canvas.removeFromLeft(m_margin * 0.25f);

    m_presetButton->setBounds(canvas);
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
