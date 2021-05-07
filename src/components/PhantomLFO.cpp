/*
  ==============================================================================

    PhantomLFO.cpp
    Created: 06 May 2021 13:26:58
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLFO.h"

#include "../utils/PhantomUtils.h"

PhantomLFOComponent::PhantomLFOComponent(AudioProcessorValueTreeState& vts) : IComponent(vts)
{
    init();
}

PhantomLFOComponent::~PhantomLFOComponent()
{
    m_lfo01RateSliderAttachment = nullptr;
    m_lfo01ShapeSliderAttachment = nullptr;

    m_lfo02RateSliderAttachment = nullptr;
    m_lfo02ShapeSliderAttachment = nullptr;
}

void PhantomLFOComponent::init()
{
    // LFO 01
    m_lfo01RateSlider = std::make_unique<Slider>();
    m_lfo01RateSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01RateSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo01RateSlider->setTextValueSuffix(" Hz");
    m_lfo01RateSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01RateSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_LFO_01_RATE_PARAM_ID, *m_lfo01RateSlider));
    addAndMakeVisible(m_lfo01RateSlider.get());

    m_lfo01ShapeSlider = std::make_unique<Slider>();
    m_lfo01ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo01ShapeSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo01ShapeSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_LFO_01_SHAPE_PARAM_ID, *m_lfo01ShapeSlider));
    addAndMakeVisible(m_lfo01ShapeSlider.get());

    // LFO 02
    m_lfo02RateSlider = std::make_unique<Slider>();
    m_lfo02RateSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02RateSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo02RateSlider->setTextValueSuffix(" Hz");
    m_lfo02RateSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo02RateSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_LFO_02_RATE_PARAM_ID, *m_lfo02RateSlider));
    addAndMakeVisible(m_lfo02RateSlider.get());

    m_lfo02ShapeSlider = std::make_unique<Slider>();
    m_lfo02ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo02ShapeSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo02ShapeSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_LFO_02_SHAPE_PARAM_ID, *m_lfo02ShapeSlider));
    addAndMakeVisible(m_lfo02ShapeSlider.get());
}

void PhantomLFOComponent::reset()
{
    m_lfo01RateSlider->setValue(Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01ShapeSlider->setValue(Consts::_LFO_01_SHAPE_DEFAULT_VAL);

    m_lfo02RateSlider->setValue(Consts::_LFO_02_RATE_DEFAULT_VAL);
    m_lfo02ShapeSlider->setValue(Consts::_LFO_02_SHAPE_DEFAULT_VAL);    
}

void PhantomLFOComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomLFOComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    Rectangle<int> lfoTopArea = canvas.removeFromTop(canvas.getHeight() / 2);
    m_lfo01RateSlider->setBounds(lfoTopArea.removeFromLeft(m_knobWidth));
    m_lfo01ShapeSlider->setBounds(lfoTopArea);

    Rectangle<int> lfoBottomArea = canvas;
    m_lfo02RateSlider->setBounds(lfoBottomArea.removeFromLeft(m_knobWidth));
    m_lfo02ShapeSlider->setBounds(lfoBottomArea);
}
