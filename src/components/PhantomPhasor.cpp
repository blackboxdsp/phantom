/*
  ==============================================================================

    PhantomPhasor.cpp
    Created: 06 May 2021 11:48:26
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomPhasor.h"
#include "../utils/PhantomUtils.h"

PhantomPhasorComponent::PhantomPhasorComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : IComponent(plf, vts)
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
    m_phasor01ShapeSlider = std::make_unique<Slider>("SEC_PHASOR_01_SHAPE");
    m_phasor01ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor01ShapeSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_01_SHAPE_DEFAULT_VAL);
    m_phasor01ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_01_SHAPE_PARAM_ID, *m_phasor01ShapeSlider));
    m_phasor01ShapeSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_phasor01ShapeSlider.get());

    m_phasor01EgIntSlider = std::make_unique<Slider>("SEC_PHASOR_01_EG_INT");
    m_phasor01EgIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01EgIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor01EgIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_01_EG_INT_DEFAULT_VAL);
    m_phasor01EgIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_01_EG_INT_PARAM_ID, *m_phasor01EgIntSlider));
    m_phasor01EgIntSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_phasor01EgIntSlider.get());

    m_phasor01LfoIntSlider = std::make_unique<Slider>("SEC_PHASOR_01_LFO_INT");
    m_phasor01LfoIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor01LfoIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor01LfoIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_01_LFO_INT_DEFAULT_VAL);
    m_phasor01LfoIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_01_LFO_INT_PARAM_ID, *m_phasor01LfoIntSlider));
    m_phasor01LfoIntSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_phasor01LfoIntSlider.get());

    // PHASOR 01
    m_phasor02ShapeSlider = std::make_unique<Slider>("SEC_PHASOR_02_SHAPE");
    m_phasor02ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor02ShapeSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_02_SHAPE_DEFAULT_VAL);
    m_phasor02ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_02_SHAPE_PARAM_ID, *m_phasor02ShapeSlider));
    m_phasor02ShapeSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_phasor02ShapeSlider.get());

    m_phasor02EgIntSlider = std::make_unique<Slider>("SEC_PHASOR_02_EG_INT");
    m_phasor02EgIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02EgIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor02EgIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_02_EG_INT_DEFAULT_VAL);
    m_phasor02EgIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_02_EG_INT_PARAM_ID, *m_phasor02EgIntSlider));
    m_phasor02EgIntSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_phasor02EgIntSlider.get());

    m_phasor02LfoIntSlider = std::make_unique<Slider>("SEC_PHASOR_02_LFO_INT");
    m_phasor02LfoIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasor02LfoIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasor02LfoIntSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_02_LFO_INT_DEFAULT_VAL);
    m_phasor02LfoIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_02_LFO_INT_PARAM_ID, *m_phasor02LfoIntSlider));
    m_phasor02LfoIntSlider->setLookAndFeel(&m_lookAndFeel);
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
    
}

void PhantomPhasorComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    canvas.removeFromBottom(m_margin * 0.5f);

    const int height = canvas.getHeight();
    
    const int phasorWidth = (canvas.getWidth() - m_margin) / 2;

    int paramWidth;

    // PHASOR 01
    Rectangle<int> phasor01Area = canvas.removeFromLeft(phasorWidth);
    paramWidth = phasor01Area.getWidth() / 2;

    Rectangle<int> phasor01ModArea = phasor01Area.removeFromLeft(paramWidth);

    Rectangle<int> phasor01EgIntArea = phasor01ModArea.removeFromTop(phasor01ModArea.getHeight() / 2);
    prepareForSlider(true, m_margin, phasor01EgIntArea);
    phasor01EgIntArea.removeFromLeft(m_margin * 0.25f);
    m_phasor01EgIntSlider->setBounds(phasor01EgIntArea);

    Rectangle<int> phasor01LfoIntArea = phasor01ModArea;
    prepareForSlider(true, m_margin, phasor01LfoIntArea);
    phasor01LfoIntArea.removeFromLeft(m_margin * 0.25f);
    m_phasor01LfoIntSlider->setBounds(phasor01LfoIntArea);
    
    Rectangle<int> phasor01ShapeArea = phasor01Area;
    phasor01Area.removeFromBottom(m_margin * 2.0f);
    prepareForSlider(getLargeSliderDiameter(), false, m_margin, phasor01ShapeArea);
    phasor01ShapeArea.removeFromLeft(m_margin * 0.25f);
    phasor01ShapeArea.removeFromBottom(m_margin * 2.0f);
    m_phasor01ShapeSlider->setBounds(phasor01ShapeArea);

    // PHASOR 02
    Rectangle<int> phasor02Area = canvas.removeFromRight(phasorWidth);
    paramWidth = phasor02Area.getWidth() / 2;

    Rectangle<int> phasor02ModArea = phasor02Area.removeFromRight(paramWidth);

    Rectangle<int> phasor02EgIntArea = phasor02ModArea.removeFromTop(phasor02ModArea.getHeight() / 2);
    prepareForSlider(true, m_margin, phasor02EgIntArea);
    phasor02EgIntArea.removeFromLeft(m_margin * 0.25f);
    m_phasor02EgIntSlider->setBounds(phasor02EgIntArea);

    Rectangle<int> phasor02LfoIntArea = phasor02ModArea;
    prepareForSlider(true, m_margin, phasor02LfoIntArea);
    phasor02LfoIntArea.removeFromLeft(m_margin * 0.25f);
    m_phasor02LfoIntSlider->setBounds(phasor02LfoIntArea);
    
    Rectangle<int> phasor02ShapeArea = phasor02Area;
    phasor02Area.removeFromBottom(m_margin * 2.0f);
    prepareForSlider(getLargeSliderDiameter(), false, m_margin, phasor02ShapeArea);
    phasor02ShapeArea.removeFromLeft(m_margin * 0.25f);
    phasor02ShapeArea.removeFromBottom(m_margin * 2.0f);
    m_phasor02ShapeSlider->setBounds(phasor02ShapeArea);
}
