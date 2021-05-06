/*
  ==============================================================================

    PhantomAmplifier.cpp
    Created: 05 May 2021 18:22:43
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomAmplifier.h"
#include "../utils/PhantomUtils.h"

PhantomAmplifierComponent::PhantomAmplifierComponent(AudioProcessorValueTreeState& vts) : IComponent(vts)
{
    init();
}

PhantomAmplifierComponent::~PhantomAmplifierComponent()
{
    m_levelSliderAttachment = nullptr;
    m_levelSlider = nullptr;
}

void PhantomAmplifierComponent::init()
{
    m_levelSlider = std::make_unique<Slider>();
    m_levelSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_levelSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_levelSlider->setTextValueSuffix(" dB");
    m_levelSlider->setDoubleClickReturnValue(true, Consts::_LEVEL_DEFAULT_VAL);
    m_levelSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_LEVEL_PARAM_ID, *m_levelSlider));
    addAndMakeVisible(m_levelSlider.get());
}

void PhantomAmplifierComponent::reset()
{
    m_levelSlider->setValue(Consts::_LEVEL_DEFAULT_VAL);
}

void PhantomAmplifierComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomAmplifierComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    canvas.removeFromTop(m_margin);
    canvas.removeFromLeft(m_margin * 2);
    canvas.removeFromRight(m_margin * 2);

    m_levelSlider->setBounds(canvas);
}
