/*
  ==============================================================================

    PhantomEnvelope.cpp
    Created: 06 May 2021 14:36:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomEnvelope.h"

#include "../utils/PhantomUtils.h"

PhantomEnvelopeComponent::PhantomEnvelopeComponent(EnvelopeType et, PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : m_type(et), IComponent(plf, vts)
{
    init();
}

PhantomEnvelopeComponent::~PhantomEnvelopeComponent()
{
    m_egAtkSliderAttachment = nullptr;
    m_egAtkSlider = nullptr;
    m_egDecSliderAttachment = nullptr;
    m_egDecSlider = nullptr;
    m_egSusSliderAttachment = nullptr;
    m_egSusSlider = nullptr;
    m_egRelSliderAttachment = nullptr;
    m_egRelSlider = nullptr;
}

void PhantomEnvelopeComponent::init()
{
    char* atkParamId;
    char* decParamId;
    char* susParamId;
    char* relParamId;

    float atkDefaultVal, decDefaultVal, susDefaultVal, relDefaultVal;

    switch(m_type)
    {
        default:
        case EnvelopeType::AMP:
            atkParamId = Consts::_AMP_EG_ATK_PARAM_ID;
            atkDefaultVal = Consts::_AMP_EG_ATK_DEFAULT_VAL;

            decParamId = Consts::_AMP_EG_DEC_PARAM_ID;
            decDefaultVal = Consts::_AMP_EG_DEC_DEFAULT_VAL;

            susParamId = Consts::_AMP_EG_SUS_PARAM_ID;
            susDefaultVal = Consts::_AMP_EG_SUS_DEFAULT_VAL;

            relParamId = Consts::_AMP_EG_REL_PARAM_ID;
            relDefaultVal = Consts::_AMP_EG_REL_DEFAULT_VAL;
            break;

        case EnvelopeType::PHASOR:
            atkParamId = Consts::_PHASOR_EG_ATK_PARAM_ID;
            atkDefaultVal = Consts::_PHASOR_EG_ATK_DEFAULT_VAL;

            decParamId = Consts::_PHASOR_EG_DEC_PARAM_ID;
            decDefaultVal = Consts::_PHASOR_EG_DEC_DEFAULT_VAL;

            susParamId = Consts::_PHASOR_EG_SUS_PARAM_ID;
            susDefaultVal = Consts::_PHASOR_EG_SUS_DEFAULT_VAL;

            relParamId = Consts::_PHASOR_EG_REL_PARAM_ID;
            relDefaultVal = Consts::_PHASOR_EG_REL_DEFAULT_VAL;
            break;

        case EnvelopeType::FILTER:
            atkParamId = Consts::_FLTR_EG_ATK_PARAM_ID;
            atkDefaultVal = Consts::_FLTR_EG_ATK_DEFAULT_VAL;

            decParamId = Consts::_FLTR_EG_DEC_PARAM_ID;
            decDefaultVal = Consts::_FLTR_EG_DEC_DEFAULT_VAL;

            susParamId = Consts::_FLTR_EG_SUS_PARAM_ID;
            susDefaultVal = Consts::_FLTR_EG_SUS_DEFAULT_VAL;

            relParamId = Consts::_FLTR_EG_REL_PARAM_ID;
            relDefaultVal = Consts::_FLTR_EG_REL_DEFAULT_VAL;
            break;

        case EnvelopeType:: MOD:
            atkParamId = Consts::_MOD_EG_ATK_PARAM_ID;
            atkDefaultVal = Consts::_MOD_EG_ATK_DEFAULT_VAL;

            decParamId = Consts::_MOD_EG_DEC_PARAM_ID;
            decDefaultVal = Consts::_MOD_EG_DEC_DEFAULT_VAL;

            susParamId = Consts::_MOD_EG_SUS_PARAM_ID;
            susDefaultVal = Consts::_MOD_EG_SUS_DEFAULT_VAL;

            relParamId = Consts::_MOD_EG_REL_PARAM_ID;
            relDefaultVal = Consts::_MOD_EG_REL_DEFAULT_VAL;
            break;
    }

    m_egAtkSlider = std::make_unique<Slider>();
    m_egAtkSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_egAtkSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_egAtkSlider->setTextValueSuffix(" s");
    m_egAtkSlider->setDoubleClickReturnValue(true, atkDefaultVal);
    m_egAtkSliderAttachment.reset(new SliderAttachment(m_parameters, atkParamId, *m_egAtkSlider));
    addAndMakeVisible(m_egAtkSlider.get());

    m_egDecSlider = std::make_unique<Slider>();
    m_egDecSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_egDecSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_egDecSlider->setTextValueSuffix(" s");
    m_egDecSlider->setDoubleClickReturnValue(true, decDefaultVal);
    m_egDecSliderAttachment.reset(new SliderAttachment(m_parameters, decParamId, *m_egDecSlider));
    addAndMakeVisible(m_egDecSlider.get());

    m_egSusSlider = std::make_unique<Slider>();
    m_egSusSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_egSusSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_egSusSlider->setTextValueSuffix(" dB");
    m_egSusSlider->setDoubleClickReturnValue(true, susDefaultVal);
    m_egSusSliderAttachment.reset(new SliderAttachment(m_parameters, susParamId, *m_egSusSlider));
    addAndMakeVisible(m_egSusSlider.get());

    m_egRelSlider = std::make_unique<Slider>();
    m_egRelSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_egRelSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_egRelSlider->setTextValueSuffix(" s");
    m_egRelSlider->setDoubleClickReturnValue(true, relDefaultVal);
    m_egRelSliderAttachment.reset(new SliderAttachment(m_parameters, relParamId, *m_egRelSlider));
    addAndMakeVisible(m_egRelSlider.get());
}

void PhantomEnvelopeComponent::reset()
{
    float atkParamVal, decParamVal, susParamVal, relParamVal;

    switch(m_type)
    {
        default:
        case EnvelopeType::AMP:
            atkParamVal = Consts::_AMP_EG_ATK_DEFAULT_VAL;
            decParamVal = Consts::_AMP_EG_DEC_DEFAULT_VAL;
            susParamVal = Consts::_AMP_EG_SUS_DEFAULT_VAL;
            relParamVal = Consts::_AMP_EG_REL_DEFAULT_VAL;
            break;

        case EnvelopeType::PHASOR:
            atkParamVal = Consts::_PHASOR_EG_ATK_DEFAULT_VAL;
            decParamVal = Consts::_PHASOR_EG_DEC_DEFAULT_VAL;
            susParamVal = Consts::_PHASOR_EG_SUS_DEFAULT_VAL;
            relParamVal = Consts::_PHASOR_EG_REL_DEFAULT_VAL;
            break;

        case EnvelopeType::FILTER:
            atkParamVal = Consts::_FLTR_EG_ATK_DEFAULT_VAL;
            decParamVal = Consts::_FLTR_EG_DEC_DEFAULT_VAL;
            susParamVal = Consts::_FLTR_EG_SUS_DEFAULT_VAL;
            relParamVal = Consts::_FLTR_EG_REL_DEFAULT_VAL;
            break;

        case EnvelopeType::MOD:
            atkParamVal = Consts::_MOD_EG_ATK_DEFAULT_VAL;
            decParamVal = Consts::_MOD_EG_DEC_DEFAULT_VAL;
            susParamVal = Consts::_MOD_EG_SUS_DEFAULT_VAL;
            relParamVal = Consts::_MOD_EG_REL_DEFAULT_VAL;
            break;
    }

    m_egAtkSlider->setValue(atkParamVal);
    m_egDecSlider->setValue(decParamVal);
    m_egSusSlider->setValue(susParamVal);
    m_egRelSlider->setValue(relParamVal);
}

void PhantomEnvelopeComponent::paint(Graphics& g)
{
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomEnvelopeComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    removeTitleSpaceFrom(m_margin * 0.35f, canvas);

    const int paramWidth = (m_windowWidth + m_margin) * (4631.0f / 38400.0f);

    Rectangle<int> egAtkArea = canvas.removeFromLeft(paramWidth);
    prepareForEgSlider(true, m_margin * 0.35f, egAtkArea);
    m_egAtkSlider->setBounds(egAtkArea);

    Rectangle<int> egDecArea = canvas.removeFromLeft(paramWidth);
    prepareForEgSlider(true, m_margin * 0.35f, egDecArea);
    egDecArea.expand(m_margin * 0.5f, 0);
    egDecArea.removeFromRight(m_margin * 0.5f);
    m_egDecSlider->setBounds(egDecArea);
    
    Rectangle<int> egSusArea = canvas.removeFromLeft(paramWidth);
    prepareForEgSlider(true, m_margin * 0.35f, egSusArea);
    egSusArea.expand(m_margin * 0.5f, 0);
    egSusArea.removeFromRight(m_margin * 0.5f);
    m_egSusSlider->setBounds(egSusArea);
    
    Rectangle<int> egRelArea = canvas.removeFromLeft(paramWidth);
    prepareForEgSlider(true, m_margin * 0.35f, egRelArea);
    egRelArea.expand(m_margin * 0.5f, 0);
    egRelArea.removeFromLeft(m_margin * 0.5f);
    m_egRelSlider->setBounds(egRelArea);
}

void PhantomEnvelopeComponent::prepareForEgSlider(const bool removeOtherHalf, const int expandBy, Rectangle <int>& bounds)
{
    if(removeOtherHalf)
            bounds.removeFromLeft(bounds.getWidth() / 2.0f);

    const int padding = (bounds.getWidth() - m_sliderDiameter) * 0.5f;

    bounds.removeFromRight(padding);
    bounds.removeFromLeft(padding);

    bounds.removeFromBottom(m_margin * 0.35f);

    if(expandBy > 0)
    {
        bounds.expand(0, expandBy);

        bounds.removeFromTop(expandBy);
    }
}
