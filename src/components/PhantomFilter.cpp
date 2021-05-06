/*
  ==============================================================================

    PhantomFilter.cpp
    Created: 06 May 2021 13:07:06
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomFilter.h"
#include "../utils/PhantomUtils.h"

PhantomFilterComponent::PhantomFilterComponent(AudioProcessorValueTreeState& vts): IComponent(vts)
{
    init();
}

PhantomFilterComponent::~PhantomFilterComponent()
{
    m_filterCutoffSliderAttachment = nullptr;
    m_filterCutoffSlider = nullptr;

    m_filterResoSliderAttachment = nullptr;
    m_filterResoSlider = nullptr;

    m_filterDriveSliderAttachment = nullptr;
    m_filterDriveSlider = nullptr;

    m_filterModeSliderAttachment = nullptr;
    m_filterModeSlider = nullptr;

    m_filterEgModDepthSliderAttachment = nullptr;
    m_filterEgModDepthSlider = nullptr;

    m_filterLfoModDepthSliderAttachment = nullptr;
    m_filterLfoModDepthSlider = nullptr;
}

void PhantomFilterComponent::init()
{
    m_filterCutoffSlider = std::make_unique<Slider>();
    m_filterCutoffSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterCutoffSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterCutoffSlider->setTextValueSuffix(" Hz");
    m_filterCutoffSlider->setDoubleClickReturnValue(true, Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterCutoffSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_CUTOFF_PARAM_ID, *m_filterCutoffSlider));
    addAndMakeVisible(m_filterCutoffSlider.get());

    m_filterResoSlider = std::make_unique<Slider>();
    m_filterResoSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterResoSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterResoSlider->setTextValueSuffix(" Q");
    m_filterResoSlider->setDoubleClickReturnValue(true, Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterResoSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_RESO_PARAM_ID, *m_filterResoSlider));
    addAndMakeVisible(m_filterResoSlider.get());

    m_filterDriveSlider = std::make_unique<Slider>();
    m_filterDriveSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterDriveSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterDriveSlider->setDoubleClickReturnValue(true, Consts::_FLTR_DRIVE_DEFAULT_VAL);
    m_filterDriveSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_DRIVE_PARAM_ID, *m_filterDriveSlider));
    addAndMakeVisible(m_filterDriveSlider.get());

    m_filterModeSlider = std::make_unique<Slider>();
    m_filterModeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterModeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterModeSlider->setDoubleClickReturnValue(true, Consts::_FLTR_MODE_DEFAULT_VAL);
    m_filterModeSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_MODE_PARAM_ID, *m_filterModeSlider));
    addAndMakeVisible(m_filterModeSlider.get());

    m_filterEgModDepthSlider = std::make_unique<Slider>();
    m_filterEgModDepthSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgModDepthSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgModDepthSlider->setDoubleClickReturnValue(true, Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterEgModDepthSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_EG_MOD_DEPTH_PARAM_ID, *m_filterEgModDepthSlider));
    addAndMakeVisible(m_filterEgModDepthSlider.get());

    m_filterLfoModDepthSlider = std::make_unique<Slider>();
    m_filterLfoModDepthSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterLfoModDepthSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterLfoModDepthSlider->setDoubleClickReturnValue(true, Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_LFO_MOD_DEPTH_PARAM_ID, *m_filterLfoModDepthSlider));
    addAndMakeVisible(m_filterLfoModDepthSlider.get());
}

void PhantomFilterComponent::reset()
{
    m_filterCutoffSlider->setValue(Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterResoSlider->setValue(Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterDriveSlider->setValue(Consts::_FLTR_DRIVE_DEFAULT_VAL);
    m_filterModeSlider->setValue(Consts::_FLTR_MODE_DEFAULT_VAL);
    m_filterEgModDepthSlider->setValue(Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSlider->setValue(Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);
}

void PhantomFilterComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomFilterComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    Rectangle<int> filterTopArea = canvas.removeFromTop(canvas.getHeight() / 2);
    m_filterCutoffSlider->setBounds(filterTopArea.removeFromLeft(m_knobWidth));
    m_filterResoSlider->setBounds(filterTopArea.removeFromLeft(m_knobWidth));
    m_filterDriveSlider->setBounds(filterTopArea);

    Rectangle<int> filterBottomArea = canvas;
    m_filterModeSlider->setBounds(filterBottomArea.removeFromLeft(m_knobWidth));
    m_filterEgModDepthSlider->setBounds(filterBottomArea.removeFromLeft(m_knobWidth));
    m_filterLfoModDepthSlider->setBounds(filterBottomArea);
}
