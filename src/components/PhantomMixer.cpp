/*
  ==============================================================================

    PhantomMixer.cpp
    Created: 06 May 2021 12:19:23
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomMixer.h"

#include "../utils/PhantomUtils.h"

PhantomMixerComponent::PhantomMixerComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts): IComponent(plf, vts)
{
    init();
}

PhantomMixerComponent::~PhantomMixerComponent()
{
    m_mixerOscBalanceSliderAttachment = nullptr;
    m_mixerOscBalanceSlider = nullptr;

    m_mixerAmpGainSliderAttachment = nullptr;
    m_mixerAmpGainSlider = nullptr;

    m_mixerRingModSliderAttachment = nullptr;
    m_mixerRingModSlider = nullptr;

    m_mixerNoiseSliderAttachment = nullptr;
    m_mixerNoiseSlider = nullptr;
}

void PhantomMixerComponent::init()
{
    m_mixerOscBalanceSlider = std::make_unique<Slider>();
    m_mixerOscBalanceSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerOscBalanceSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerOscBalanceSlider->setDoubleClickReturnValue(true, Consts::_MIXER_OSC_BAL_DEFAULT_VAL);
    m_mixerOscBalanceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_OSC_BAL_PARAM_ID, *m_mixerOscBalanceSlider));
    addAndMakeVisible(m_mixerOscBalanceSlider.get());

    m_mixerAmpGainSlider = std::make_unique<Slider>();
    m_mixerAmpGainSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerAmpGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerAmpGainSlider->setDoubleClickReturnValue(true, Consts::_MIXER_AMP_GAIN_DEFAULT_VAL);
    m_mixerAmpGainSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_AMP_GAIN_PARAM_ID, *m_mixerAmpGainSlider));
    addAndMakeVisible(m_mixerAmpGainSlider.get());

    m_mixerRingModSlider = std::make_unique<Slider>();
    m_mixerRingModSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerRingModSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerRingModSlider->setDoubleClickReturnValue(true, Consts::_MIXER_RING_MOD_DEFAULT_VAL);
    m_mixerRingModSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_RING_MOD_PARAM_ID, *m_mixerRingModSlider));
    addAndMakeVisible(m_mixerRingModSlider.get());

    m_mixerNoiseSlider = std::make_unique<Slider>();
    m_mixerNoiseSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerNoiseSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerNoiseSlider->setDoubleClickReturnValue(true, Consts::_MIXER_NOISE_DEFAULT_VAL);
    m_mixerNoiseSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_NOISE_PARAM_ID, *m_mixerNoiseSlider));
    addAndMakeVisible(m_mixerNoiseSlider.get());
}

void PhantomMixerComponent::reset()
{
    m_mixerOscBalanceSlider->setValue(Consts::_MIXER_OSC_BAL_DEFAULT_VAL);
    m_mixerAmpGainSlider->setValue(Consts::_MIXER_AMP_GAIN_DEFAULT_VAL);
    m_mixerRingModSlider->setValue(Consts::_MIXER_RING_MOD_DEFAULT_VAL);
    m_mixerNoiseSlider->setValue(Consts::_MIXER_NOISE_DEFAULT_VAL);
}

void PhantomMixerComponent::paint(Graphics& g)
{
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomMixerComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    canvas.removeFromBottom(m_margin);

    const int height = canvas.getHeight();
    const int width = canvas.getWidth();

    // TOP
    Rectangle<int> topArea = canvas.removeFromTop(height / 2);

    topArea.removeFromTop(m_margin * 0.125f);
    topArea.removeFromBottom(m_margin * 0.125f);

    Rectangle<int> oscBalanceArea = topArea.removeFromLeft(width / 2);
    prepareForSlider(true, m_margin, oscBalanceArea);
    m_mixerOscBalanceSlider->setBounds(oscBalanceArea);

    Rectangle<int> ampGainArea = topArea.removeFromRight(width / 2);
    prepareForSlider(true, m_margin, ampGainArea);
    m_mixerAmpGainSlider->setBounds(ampGainArea);

    // BOTTOM
    Rectangle<int> bottomArea = canvas.removeFromBottom(height / 2);

    bottomArea.removeFromTop(m_margin * 0.25f);

    Rectangle<int> ringModArea = bottomArea.removeFromLeft(width / 2);
    prepareForSlider(true, m_margin, ringModArea);
    m_mixerRingModSlider->setBounds(ringModArea);

    Rectangle<int> noiseArea = bottomArea.removeFromRight(width / 2);
    prepareForSlider(true, m_margin, noiseArea);
    m_mixerNoiseSlider->setBounds(noiseArea);
}
