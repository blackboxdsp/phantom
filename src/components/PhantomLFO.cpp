/*
  ==============================================================================

    PhantomLFO.cpp
    Created: 06 May 2021 13:26:58
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLFO.h"

#include "../utils/PhantomUtils.h"

PhantomLFOComponent::PhantomLFOComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : IComponent(plf, vts)
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
    m_lfo01RateSlider = std::make_unique<Slider>("PRI_LFO_01_RATE");
    m_lfo01RateSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01RateSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo01RateSlider->setTextValueSuffix(" Hz");
    m_lfo01RateSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01RateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_01_RATE_PARAM_ID, *m_lfo01RateSlider));
    m_lfo01RateSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_lfo01RateSlider.get());

    m_lfo01ShapeSlider = std::make_unique<Slider>("PRI_LFO_01_SHAPE");
    m_lfo01ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo01ShapeSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo01ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_01_SHAPE_PARAM_ID, *m_lfo01ShapeSlider));
    m_lfo01ShapeSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_lfo01ShapeSlider.get());

    // LFO 02
    m_lfo02RateSlider = std::make_unique<Slider>("PRI_LFO_02_RATE");
    m_lfo02RateSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02RateSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo02RateSlider->setTextValueSuffix(" Hz");
    m_lfo02RateSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo02RateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_02_RATE_PARAM_ID, *m_lfo02RateSlider));
    m_lfo02RateSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_lfo02RateSlider.get());

    m_lfo02ShapeSlider = std::make_unique<Slider>("PRI_LFO_02_SHAPE");
    m_lfo02ShapeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02ShapeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo02ShapeSlider->setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo02ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_02_SHAPE_PARAM_ID, *m_lfo02ShapeSlider));
    m_lfo02ShapeSlider->setLookAndFeel(&m_lookAndFeel);
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
    
}

void PhantomLFOComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    canvas.removeFromBottom(m_margin);

    const int height = canvas.getHeight();
    const int width = canvas.getWidth() - (m_margin * 0.25f);

    // TOP
    Rectangle<int> topArea = canvas.removeFromTop(height / 2);

    Rectangle<int> lfo01RateArea = topArea.removeFromLeft(width / 2);
    prepareForSlider(true, m_margin * 0.9, lfo01RateArea);
    lfo01RateArea.removeFromRight(m_margin * 0.25f);
    m_lfo01RateSlider->setBounds(lfo01RateArea);

    Rectangle<int> lfo02RateArea = topArea.removeFromRight(width / 2);
    prepareForSlider(true, m_margin * 0.9, lfo02RateArea);
    lfo02RateArea.removeFromLeft(m_margin * 0.25f);
    m_lfo02RateSlider->setBounds(lfo02RateArea);

    // BOTTOM
    Rectangle<int> bottomArea = canvas.removeFromBottom(height / 2);

    bottomArea.removeFromTop(m_margin * 0.25f);

    Rectangle<int> lfo01ShapeArea = bottomArea.removeFromLeft(width / 2);
    prepareForSlider(true, m_margin, lfo01ShapeArea);
    lfo01ShapeArea.removeFromRight(m_margin * 0.25f);
    m_lfo01ShapeSlider->setBounds(lfo01ShapeArea);

    Rectangle<int> lfo02ShapeArea = bottomArea.removeFromRight(width / 2);
    prepareForSlider(true, m_margin, lfo02ShapeArea);
    lfo02ShapeArea.removeFromLeft(m_margin * 0.25f);
    m_lfo02ShapeSlider->setBounds(lfo02ShapeArea);
}
