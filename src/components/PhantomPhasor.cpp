/*
  ==============================================================================

    PhantomPhasor.cpp
    Created: 06 May 2021 11:48:26
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomPhasor.h"
#include "../utils/PhantomUtils.h"

PhantomPhasorComponent::PhantomPhasorComponent(AudioProcessorValueTreeState& vts) : IComponent(vts)
{
    init();
}

PhantomPhasorComponent::~PhantomPhasorComponent()
{
    m_phasor01ShapeSliderAttachment = nullptr;
    m_phasor01ShapeSlider = nullptr;
    m_phasor01EgIntSliderAttachment = nullptr;
    m_phasor01EgIntSlider = nullptr;
    m_phasor01LfoIntSliderAttachment = nullptr;
    m_phasor01LfoIntSlider = nullptr;

    m_phasor02ShapeSliderAttachment = nullptr;
    m_phasor02ShapeSlider = nullptr;
    m_phasor02EgIntSliderAttachment = nullptr;
    m_phasor02EgIntSlider = nullptr;
    m_phasor02LfoIntSliderAttachment = nullptr;
    m_phasor02LfoIntSlider = nullptr;
}

void PhantomPhasorComponent::init()
{
    // PHASOR 01
    m_phasor01ShapeSlider = std::make_unique<Slider>();
    m_phasor01ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor01ShapeSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_01_SHAPE_DEFAULT_VAL);
    m_phasor01ShapeSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_01_SHAPE_PARAM_ID, *m_phasor01ShapeSlider));
    addAndMakeVisible(m_phasor01ShapeSlider.get());

    m_phasor01EgIntSlider = std::make_unique<Slider>();
    m_phasor01EgIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01EgIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor01EgIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_01_EG_INT_DEFAULT_VAL);
    m_phasor01EgIntSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_01_EG_INT_PARAM_ID, *m_phasor01EgIntSlider));
    addAndMakeVisible(m_phasor01EgIntSlider.get());

    m_phasor01LfoIntSlider = std::make_unique<Slider>();
    m_phasor01LfoIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01LfoIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor01LfoIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_01_LFO_INT_DEFAULT_VAL);
    m_phasor01LfoIntSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_01_LFO_INT_PARAM_ID, *m_phasor01LfoIntSlider));
    addAndMakeVisible(m_phasor01LfoIntSlider.get());

    // PHASOR 01
    m_phasor02ShapeSlider = std::make_unique<Slider>();
    m_phasor02ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor02ShapeSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_02_SHAPE_DEFAULT_VAL);
    m_phasor02ShapeSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_02_SHAPE_PARAM_ID, *m_phasor02ShapeSlider));
    addAndMakeVisible(m_phasor02ShapeSlider.get());

    m_phasor02EgIntSlider = std::make_unique<Slider>();
    m_phasor02EgIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02EgIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor02EgIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_02_EG_INT_DEFAULT_VAL);
    m_phasor02EgIntSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_02_EG_INT_PARAM_ID, *m_phasor02EgIntSlider));
    addAndMakeVisible(m_phasor02EgIntSlider.get());

    m_phasor02LfoIntSlider = std::make_unique<Slider>();
    m_phasor02LfoIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02LfoIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor02LfoIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_02_LFO_INT_DEFAULT_VAL);
    m_phasor02LfoIntSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_02_LFO_INT_PARAM_ID, *m_phasor02LfoIntSlider));
    addAndMakeVisible(m_phasor02LfoIntSlider.get());
}

void PhantomPhasorComponent::reset()
{
    m_phasor01ShapeSlider->setValue(Consts::_PHASOR_01_SHAPE_DEFAULT_VAL);
    m_phasor01EgIntSlider->setValue(Consts::_PHASOR_01_EG_INT_DEFAULT_VAL);
    m_phasor01LfoIntSlider->setValue(Consts::_PHASOR_01_LFO_INT_DEFAULT_VAL);

    m_phasor02ShapeSlider->setValue(Consts::_PHASOR_02_SHAPE_DEFAULT_VAL);
    m_phasor02EgIntSlider->setValue(Consts::_PHASOR_02_EG_INT_DEFAULT_VAL);
    m_phasor02LfoIntSlider->setValue(Consts::_PHASOR_02_LFO_INT_DEFAULT_VAL);
}

void PhantomPhasorComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomPhasorComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    Rectangle<int> phasor01Area = canvas.removeFromTop(canvas.getHeight() / 2);
    m_phasor01ShapeSlider->setBounds(phasor01Area.removeFromLeft(m_knobWidth));
    m_phasor01EgIntSlider->setBounds(phasor01Area.removeFromLeft(m_knobWidth));
    m_phasor01LfoIntSlider->setBounds(phasor01Area);

    Rectangle<int> phasor02Area = canvas;
    m_phasor02ShapeSlider->setBounds(phasor02Area.removeFromLeft(m_knobWidth));
    m_phasor02EgIntSlider->setBounds(phasor02Area.removeFromLeft(m_knobWidth));
    m_phasor02LfoIntSlider->setBounds(phasor02Area);
}
