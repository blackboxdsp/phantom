/*
  ==============================================================================

    PhantomEnvelope.cpp
    Created: 06 May 2021 14:36:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomEnvelope.h"

#include "../utils/PhantomUtils.h"

PhantomEnvelopeComponent::PhantomEnvelopeComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : IComponent(plf, vts)
{
    init();
}

PhantomEnvelopeComponent::~PhantomEnvelopeComponent()
{
    m_ampEgAtkSliderAttachment = nullptr;
    m_ampEgAtkSlider = nullptr;
    m_ampEgDecSliderAttachment = nullptr;
    m_ampEgDecSlider = nullptr;
    m_ampEgSusSliderAttachment = nullptr;
    m_ampEgSusSlider = nullptr;
    m_ampEgRelSliderAttachment = nullptr;
    m_ampEgRelSlider = nullptr;

    m_phasorEgAtkSliderAttachment = nullptr;
    m_phasorEgAtkSlider = nullptr;
    m_phasorEgDecSliderAttachment = nullptr;
    m_phasorEgDecSlider = nullptr;
    m_phasorEgSusSliderAttachment = nullptr;
    m_phasorEgSusSlider = nullptr;
    m_phasorEgRelSliderAttachment = nullptr;
    m_phasorEgRelSlider = nullptr;

    m_filterEgAtkSliderAttachment = nullptr;
    m_filterEgAtkSlider = nullptr;
    m_filterEgDecSliderAttachment = nullptr;
    m_filterEgDecSlider = nullptr;
    m_filterEgSusSliderAttachment = nullptr;
    m_filterEgSusSlider = nullptr;
    m_filterEgRelSliderAttachment = nullptr;
    m_filterEgRelSlider = nullptr;

    m_modEgAtkSliderAttachment = nullptr;
    m_modEgAtkSlider = nullptr;
    m_modEgDecSliderAttachment = nullptr;
    m_modEgDecSlider = nullptr;
    m_modEgSusSliderAttachment = nullptr;
    m_modEgSusSlider = nullptr;
    m_modEgRelSliderAttachment = nullptr;
    m_modEgRelSlider = nullptr;
}

void PhantomEnvelopeComponent::init()
{
    initAmpEnvelope();
    initPhasorEnvelope();
    initFilterEnvelope();
    initModEnvelope();
}

void PhantomEnvelopeComponent::initAmpEnvelope()
{
    m_ampEgAtkSlider = std::make_unique<Slider>();
    m_ampEgAtkSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgAtkSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgAtkSlider->setTextValueSuffix(" s");
    m_ampEgAtkSlider->setDoubleClickReturnValue(true, Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgAtkSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_AMP_EG_ATK_PARAM_ID, *m_ampEgAtkSlider));
    addAndMakeVisible(m_ampEgAtkSlider.get());

    m_ampEgDecSlider = std::make_unique<Slider>();
    m_ampEgDecSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgDecSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgDecSlider->setTextValueSuffix(" s");
    m_ampEgDecSlider->setDoubleClickReturnValue(true, Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgDecSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_AMP_EG_DEC_PARAM_ID, *m_ampEgDecSlider));
    addAndMakeVisible(m_ampEgDecSlider.get());

    m_ampEgSusSlider = std::make_unique<Slider>();
    m_ampEgSusSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgSusSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgSusSlider->setTextValueSuffix(" dB");
    m_ampEgSusSlider->setDoubleClickReturnValue(true, Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgSusSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_AMP_EG_SUS_PARAM_ID, *m_ampEgSusSlider));
    addAndMakeVisible(m_ampEgSusSlider.get());

    m_ampEgRelSlider = std::make_unique<Slider>();
    m_ampEgRelSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgRelSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgRelSlider->setTextValueSuffix(" s");
    m_ampEgRelSlider->setDoubleClickReturnValue(true, Consts::_AMP_EG_REL_DEFAULT_VAL);
    m_ampEgRelSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_AMP_EG_REL_PARAM_ID, *m_ampEgRelSlider));
    addAndMakeVisible(m_ampEgRelSlider.get());
}

void PhantomEnvelopeComponent::initPhasorEnvelope()
{
    m_phasorEgAtkSlider = std::make_unique<Slider>();
    m_phasorEgAtkSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgAtkSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgAtkSlider->setTextValueSuffix(" s");
    m_phasorEgAtkSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgAtkSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_EG_ATK_PARAM_ID, *m_phasorEgAtkSlider));
    addAndMakeVisible(m_phasorEgAtkSlider.get());

    m_phasorEgDecSlider = std::make_unique<Slider>();
    m_phasorEgDecSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgDecSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgDecSlider->setTextValueSuffix(" s");
    m_phasorEgDecSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgDecSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_EG_DEC_PARAM_ID, *m_phasorEgDecSlider));
    addAndMakeVisible(m_phasorEgDecSlider.get());

    m_phasorEgSusSlider = std::make_unique<Slider>();
    m_phasorEgSusSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgSusSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgSusSlider->setTextValueSuffix(" dB");
    m_phasorEgSusSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgSusSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_EG_SUS_PARAM_ID, *m_phasorEgSusSlider));
    addAndMakeVisible(m_phasorEgSusSlider.get());

    m_phasorEgRelSlider = std::make_unique<Slider>();
    m_phasorEgRelSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgRelSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgRelSlider->setTextValueSuffix(" s");
    m_phasorEgRelSlider->setDoubleClickReturnValue(true, Consts::_PHASOR_EG_REL_DEFAULT_VAL);
    m_phasorEgRelSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_PHASOR_EG_REL_PARAM_ID, *m_phasorEgRelSlider));
    addAndMakeVisible(m_phasorEgRelSlider.get());
}

void PhantomEnvelopeComponent::initFilterEnvelope()
{
    m_filterEgAtkSlider = std::make_unique<Slider>();
    m_filterEgAtkSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgAtkSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgAtkSlider->setTextValueSuffix(" s");
    m_filterEgAtkSlider->setDoubleClickReturnValue(true, Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgAtkSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_EG_ATK_PARAM_ID, *m_filterEgAtkSlider));
    addAndMakeVisible(m_filterEgAtkSlider.get());

    m_filterEgDecSlider = std::make_unique<Slider>();
    m_filterEgDecSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgDecSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgDecSlider->setTextValueSuffix(" s");
    m_filterEgDecSlider->setDoubleClickReturnValue(true, Consts::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgDecSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_EG_DEC_PARAM_ID, *m_filterEgDecSlider));
    addAndMakeVisible(m_filterEgDecSlider.get());

    m_filterEgSusSlider = std::make_unique<Slider>();
    m_filterEgSusSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgSusSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgSusSlider->setTextValueSuffix(" dB");
    m_filterEgSusSlider->setDoubleClickReturnValue(true, Consts::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgSusSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_EG_SUS_PARAM_ID, *m_filterEgSusSlider));
    addAndMakeVisible(m_filterEgSusSlider.get());

    m_filterEgRelSlider = std::make_unique<Slider>();
    m_filterEgRelSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgRelSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgRelSlider->setTextValueSuffix(" s");
    m_filterEgRelSlider->setDoubleClickReturnValue(true, Consts::_FLTR_EG_REL_DEFAULT_VAL);
    m_filterEgRelSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_FLTR_EG_REL_PARAM_ID, *m_filterEgRelSlider));
    addAndMakeVisible(m_filterEgRelSlider.get());
}

void PhantomEnvelopeComponent::initModEnvelope()
{
    m_modEgAtkSlider = std::make_unique<Slider>();
    m_modEgAtkSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgAtkSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgAtkSlider->setTextValueSuffix(" s");
    m_modEgAtkSlider->setDoubleClickReturnValue(true, Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgAtkSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_MOD_EG_ATK_PARAM_ID, *m_modEgAtkSlider));
    addAndMakeVisible(m_modEgAtkSlider.get());

    m_modEgDecSlider = std::make_unique<Slider>();
    m_modEgDecSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgDecSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgDecSlider->setTextValueSuffix(" s");
    m_modEgDecSlider->setDoubleClickReturnValue(true, Consts::_MOD_EG_DEC_DEFAULT_VAL);
    m_modEgDecSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_MOD_EG_DEC_PARAM_ID, *m_modEgDecSlider));
    addAndMakeVisible(m_modEgDecSlider.get());

    m_modEgSusSlider = std::make_unique<Slider>();
    m_modEgSusSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgSusSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgSusSlider->setTextValueSuffix(" dB");
    m_modEgSusSlider->setDoubleClickReturnValue(true, Consts::_MOD_EG_SUS_DEFAULT_VAL);
    m_modEgSusSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_MOD_EG_SUS_PARAM_ID, *m_modEgSusSlider));
    addAndMakeVisible(m_modEgSusSlider.get());

    m_modEgRelSlider = std::make_unique<Slider>();
    m_modEgRelSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgRelSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgRelSlider->setTextValueSuffix(" s");
    m_modEgRelSlider->setDoubleClickReturnValue(true, Consts::_MOD_EG_REL_DEFAULT_VAL);
    m_modEgRelSliderAttachment.reset(new SliderAttachment(*m_parameters, Consts::_MOD_EG_REL_PARAM_ID, *m_modEgRelSlider));
    addAndMakeVisible(m_modEgRelSlider.get());
}

void PhantomEnvelopeComponent::reset()
{
    m_ampEgAtkSlider->setValue(Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgDecSlider->setValue(Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgSusSlider->setValue(Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgRelSlider->setValue(Consts::_AMP_EG_REL_DEFAULT_VAL);

    m_filterEgAtkSlider->setValue(Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgDecSlider->setValue(Consts::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgSusSlider->setValue(Consts::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgRelSlider->setValue(Consts::_FLTR_EG_REL_DEFAULT_VAL);

    m_phasorEgAtkSlider->setValue(Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgDecSlider->setValue(Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgSusSlider->setValue(Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgRelSlider->setValue(Consts::_PHASOR_EG_REL_DEFAULT_VAL);

    m_modEgAtkSlider->setValue(Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgDecSlider->setValue(Consts::_MOD_EG_DEC_DEFAULT_VAL);
    m_modEgSusSlider->setValue(Consts::_MOD_EG_SUS_DEFAULT_VAL);
    m_modEgRelSlider->setValue(Consts::_MOD_EG_REL_DEFAULT_VAL);
}

void PhantomEnvelopeComponent::paint(Graphics& g)
{
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomEnvelopeComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    Rectangle<int> bottomTopArea = canvas.removeFromTop(canvas.getHeight() / 2);
    Rectangle<int> ampEgArea = bottomTopArea.removeFromLeft(m_knobWidth * 4);
    bottomTopArea.removeFromLeft(m_margin);
    m_ampEgAtkSlider->setBounds(ampEgArea.removeFromLeft(m_knobWidth));
    m_ampEgDecSlider->setBounds(ampEgArea.removeFromLeft(m_knobWidth));
    m_ampEgSusSlider->setBounds(ampEgArea.removeFromLeft(m_knobWidth));
    m_ampEgRelSlider->setBounds(ampEgArea.removeFromLeft(m_knobWidth));

    Rectangle<int> phasorEgArea = bottomTopArea;
    m_phasorEgAtkSlider->setBounds(phasorEgArea.removeFromLeft(m_knobWidth));
    m_phasorEgDecSlider->setBounds(phasorEgArea.removeFromLeft(m_knobWidth));
    m_phasorEgSusSlider->setBounds(phasorEgArea.removeFromLeft(m_knobWidth));
    m_phasorEgRelSlider->setBounds(phasorEgArea.removeFromLeft(m_knobWidth));

    Rectangle<int> bottomBottomArea = canvas;
    Rectangle<int> filterEgArea = bottomBottomArea.removeFromLeft(m_knobWidth * 4);
    bottomBottomArea.removeFromLeft(m_margin);
    m_filterEgAtkSlider->setBounds(filterEgArea.removeFromLeft(m_knobWidth));
    m_filterEgDecSlider->setBounds(filterEgArea.removeFromLeft(m_knobWidth));
    m_filterEgSusSlider->setBounds(filterEgArea.removeFromLeft(m_knobWidth));
    m_filterEgRelSlider->setBounds(filterEgArea.removeFromLeft(m_knobWidth));

    Rectangle<int> modEgArea = bottomBottomArea;
    m_modEgAtkSlider->setBounds(modEgArea.removeFromLeft(m_knobWidth));
    m_modEgDecSlider->setBounds(modEgArea.removeFromLeft(m_knobWidth));
    m_modEgSusSlider->setBounds(modEgArea.removeFromLeft(m_knobWidth));
    m_modEgRelSlider->setBounds(modEgArea.removeFromLeft(m_knobWidth));
}
