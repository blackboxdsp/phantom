/*
  ==============================================================================

    PhnatomOscillator.cpp
    Created: 06 May 2021 08:20:43
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomOscillator.h"

#include "../utils/PhantomUtils.h"

PhantomOscillatorComponent::PhantomOscillatorComponent(PhantomLookAndFeel& plf, AudioProcessorValueTreeState& vts) : IComponent(plf, vts)
{
    init();
}

PhantomOscillatorComponent::~PhantomOscillatorComponent()
{
    m_oscSyncSliderAttachment = nullptr;
    m_oscSyncSlider = nullptr;

    m_osc01RangeSliderAttachment = nullptr;
    m_osc01RangeSlider = nullptr;
    m_osc01CoarseTuneSliderAttachment = nullptr;
    m_osc01CoarseTuneSlider = nullptr;
    m_osc01FineTuneSliderAttachment = nullptr;
    m_osc01FineTuneSlider = nullptr;
    m_osc01ShapeIntSliderAttachment = nullptr;
    m_osc01ShapeIntSlider = nullptr;
    m_osc01ModDepthSliderAttachment = nullptr;
    m_osc01ModDepthSlider = nullptr;
    m_osc01ModSourceSliderAttachment = nullptr;
    m_osc01ModSourceSlider = nullptr;

    m_osc02RangeSliderAttachment = nullptr;
    m_osc02RangeSlider = nullptr;
    m_osc02CoarseTuneSliderAttachment = nullptr;
    m_osc02CoarseTuneSlider = nullptr;
    m_osc02FineTuneSliderAttachment = nullptr;
    m_osc02FineTuneSlider = nullptr;
    m_osc02ShapeIntSliderAttachment = nullptr;
    m_osc02ShapeIntSlider = nullptr;
    m_osc02ModDepthSliderAttachment = nullptr;
    m_osc02ModDepthSlider = nullptr;
    m_osc02ModSourceSliderAttachment = nullptr;
    m_osc02ModSourceSlider = nullptr;
}

void PhantomOscillatorComponent::init()
{
    m_oscSyncSlider = std::make_unique<Slider>("PRI_OSC_SYNC");
    m_oscSyncSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_oscSyncSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_oscSyncSlider->setDoubleClickReturnValue(true, Consts::_OSC_SYNC_DEFAULT_VAL);
    m_oscSyncSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_SYNC_PARAM_ID, *m_oscSyncSlider));
    m_oscSyncSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_oscSyncSlider.get());

    // OSCILLATOR 01
    m_osc01RangeSlider = std::make_unique<Slider>("PRI_OSC_01_RANGE");
    m_osc01RangeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01RangeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc01RangeSlider->setTextValueSuffix("'");
    m_osc01RangeSlider->setDoubleClickReturnValue(true, Consts::_OSC_01_RANGE_DEFAULT_VAL);
    m_osc01RangeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_RANGE_PARAM_ID, *m_osc01RangeSlider));
    m_osc01RangeSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc01RangeSlider.get());

    m_osc01CoarseTuneSlider = std::make_unique<Slider>("PRI_OSC_01_COARSE_TUNE");
    m_osc01CoarseTuneSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01CoarseTuneSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc01CoarseTuneSlider->setDoubleClickReturnValue(true, Consts::_OSC_01_COARSE_TUNE_DEFAULT_VAL);
    m_osc01CoarseTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_COARSE_TUNE_PARAM_ID, *m_osc01CoarseTuneSlider));
    m_osc01CoarseTuneSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc01CoarseTuneSlider.get());

    m_osc01FineTuneSlider = std::make_unique<Slider>("PRI_OSC_01_FINE_TUNE");
    m_osc01FineTuneSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01FineTuneSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc01FineTuneSlider->setDoubleClickReturnValue(true, Consts::_OSC_01_FINE_TUNE_DEFAULT_VAL);
    m_osc01FineTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_FINE_TUNE_PARAM_ID, *m_osc01FineTuneSlider));
    m_osc01FineTuneSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc01FineTuneSlider.get());

    m_osc01ModDepthSlider = std::make_unique<Slider>("PRI_OSC_01_MOD_DEPTH");
    m_osc01ModDepthSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01ModDepthSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc01ModDepthSlider->setDoubleClickReturnValue(true, Consts::_OSC_01_MOD_DEPTH_DEFAULT_VAL);
    m_osc01ModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_MOD_DEPTH_PARAM_ID, *m_osc01ModDepthSlider));
    m_osc01ModDepthSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc01ModDepthSlider.get());

    m_osc01ModSourceSlider = std::make_unique<Slider>("PRI_OSC_01_MOD_SOURCE");
    m_osc01ModSourceSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01ModSourceSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc01ModSourceSlider->setDoubleClickReturnValue(true, Consts::_OSC_01_MOD_SOURCE_DEFAULT_VAL);
    m_osc01ModSourceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_MOD_SOURCE_PARAM_ID, *m_osc01ModSourceSlider));
    m_osc01ModSourceSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc01ModSourceSlider.get());

    m_osc01ShapeIntSlider = std::make_unique<Slider>("PRI_OSC_01_SHAPE_INT");
    m_osc01ShapeIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc01ShapeIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc01ShapeIntSlider->setDoubleClickReturnValue(true, Consts::_OSC_01_SHAPE_INT_DEFAULT_VAL);
    m_osc01ShapeIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_01_SHAPE_INT_PARAM_ID, *m_osc01ShapeIntSlider));
    m_osc01ShapeIntSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc01ShapeIntSlider.get());

    // OSCILLATOR 02
    m_osc02RangeSlider = std::make_unique<Slider>("PRI_OSC_02_RANGE");
    m_osc02RangeSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02RangeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc02RangeSlider->setTextValueSuffix("'");
    m_osc02RangeSlider->setDoubleClickReturnValue(true, Consts::_OSC_02_RANGE_DEFAULT_VAL);
    m_osc02RangeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_RANGE_PARAM_ID, *m_osc02RangeSlider));
    m_osc02RangeSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc02RangeSlider.get());

    m_osc02CoarseTuneSlider = std::make_unique<Slider>("PRI_OSC_02_COARSE_TUNE");
    m_osc02CoarseTuneSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02CoarseTuneSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc02CoarseTuneSlider->setDoubleClickReturnValue(true, Consts::_OSC_02_COARSE_TUNE_DEFAULT_VAL);
    m_osc02CoarseTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_COARSE_TUNE_PARAM_ID, *m_osc02CoarseTuneSlider));
    m_osc02CoarseTuneSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc02CoarseTuneSlider.get());

    m_osc02FineTuneSlider = std::make_unique<Slider>("PRI_OSC_02_FINE_TUNE");
    m_osc02FineTuneSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02FineTuneSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc02FineTuneSlider->setDoubleClickReturnValue(true, Consts::_OSC_02_FINE_TUNE_DEFAULT_VAL);
    m_osc02FineTuneSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_FINE_TUNE_PARAM_ID, *m_osc02FineTuneSlider));
    m_osc02FineTuneSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc02FineTuneSlider.get());

    m_osc02ModDepthSlider = std::make_unique<Slider>("PRI_OSC_02_MOD_DEPTH");
    m_osc02ModDepthSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02ModDepthSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc02ModDepthSlider->setDoubleClickReturnValue(true, Consts::_OSC_02_MOD_DEPTH_DEFAULT_VAL);
    m_osc02ModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_MOD_DEPTH_PARAM_ID, *m_osc02ModDepthSlider));
    m_osc02ModDepthSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc02ModDepthSlider.get());

    m_osc02ModSourceSlider = std::make_unique<Slider>("PRI_OSC_02_MOD_SOURCE");
    m_osc02ModSourceSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02ModSourceSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc02ModSourceSlider->setDoubleClickReturnValue(true, Consts::_OSC_02_MOD_SOURCE_DEFAULT_VAL);
    m_osc02ModSourceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_MOD_SOURCE_PARAM_ID, *m_osc02ModSourceSlider));
    m_osc02ModSourceSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc02ModSourceSlider.get());

    m_osc02ShapeIntSlider = std::make_unique<Slider>("PRI_OSC_02_SHAPE_INT");
    m_osc02ShapeIntSlider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_osc02ShapeIntSlider->setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_osc02ShapeIntSlider->setDoubleClickReturnValue(true, Consts::_OSC_02_SHAPE_INT_DEFAULT_VAL);
    m_osc02ShapeIntSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_OSC_02_SHAPE_INT_PARAM_ID, *m_osc02ShapeIntSlider));
    m_osc02ShapeIntSlider->setLookAndFeel(&m_lookAndFeel);
    addAndMakeVisible(m_osc02ShapeIntSlider.get());
}

void PhantomOscillatorComponent::reset()
{
    m_oscSyncSlider->setValue(Consts::_OSC_SYNC_DEFAULT_VAL);
    
    m_osc01RangeSlider->setValue(Consts::_OSC_01_RANGE_DEFAULT_VAL);
    m_osc01CoarseTuneSlider->setValue(Consts::_OSC_01_COARSE_TUNE_DEFAULT_VAL);
    m_osc01FineTuneSlider->setValue(Consts::_OSC_01_FINE_TUNE_DEFAULT_VAL);
    m_osc01ShapeIntSlider->setValue(Consts::_OSC_01_SHAPE_INT_DEFAULT_VAL);
    m_osc01ModDepthSlider->setValue(Consts::_OSC_01_MOD_DEPTH_DEFAULT_VAL);
    m_osc01ModSourceSlider->setValue(Consts::_OSC_01_MOD_SOURCE_DEFAULT_VAL);

    m_osc02RangeSlider->setValue(Consts::_OSC_02_RANGE_DEFAULT_VAL);
    m_osc02CoarseTuneSlider->setValue(Consts::_OSC_02_COARSE_TUNE_DEFAULT_VAL);
    m_osc02FineTuneSlider->setValue(Consts::_OSC_02_FINE_TUNE_DEFAULT_VAL);
    m_osc02ShapeIntSlider->setValue(Consts::_OSC_02_SHAPE_INT_DEFAULT_VAL);
    m_osc02ModDepthSlider->setValue(Consts::_OSC_02_MOD_DEPTH_DEFAULT_VAL);
    m_osc02ModSourceSlider->setValue(Consts::_OSC_02_MOD_SOURCE_DEFAULT_VAL);
}

void PhantomOscillatorComponent::paint(Graphics& g)
{
    
}

void PhantomOscillatorComponent::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    canvas.removeFromTop(m_margin * 0.75f);
    canvas.removeFromBottom(m_margin * 0.5f);

    const int height = canvas.getHeight();

    // OSC 01
    Rectangle<int> oscillator01Area = canvas.removeFromLeft(m_windowWidth * (6553.0f / 19200.0f));

    int paramWidth = oscillator01Area.getWidth() / 3;

    Rectangle<int> oscillator01LeftArea = oscillator01Area.removeFromLeft(paramWidth);

    Rectangle<int> oscillator01RangeArea = oscillator01LeftArea.removeFromTop(height / 2);
    prepareForSlider(true, m_margin, oscillator01RangeArea);
    oscillator01RangeArea.expand(0, m_margin * 0.25f);
    oscillator01RangeArea.removeFromTop(m_margin * 0.25f);
    m_osc01RangeSlider->setBounds(oscillator01RangeArea);
    
    Rectangle<int> oscillator01ShapeArea = oscillator01LeftArea.removeFromBottom(height / 2);
    prepareForSlider(true, m_margin, oscillator01ShapeArea);
    m_osc01ShapeIntSlider->setBounds(oscillator01ShapeArea);

    Rectangle<int> oscillator01MiddleArea = oscillator01Area.removeFromLeft(paramWidth);

    Rectangle<int> oscillator01CoarseTuneArea = oscillator01MiddleArea.removeFromTop(height / 2);
    prepareForSlider(true, m_margin, oscillator01CoarseTuneArea);
    oscillator01CoarseTuneArea.expand(0, m_margin * 0.25f);
    oscillator01CoarseTuneArea.removeFromTop(m_margin * 0.25f);
    m_osc01CoarseTuneSlider->setBounds(oscillator01CoarseTuneArea);
    
    Rectangle<int> oscillator01ModSourceArea = oscillator01MiddleArea.removeFromBottom(height / 2);
    prepareForSlider(true, m_margin, oscillator01ModSourceArea);
    m_osc01ModSourceSlider->setBounds(oscillator01ModSourceArea);

    Rectangle<int> oscillator01RightArea = oscillator01Area.removeFromLeft(paramWidth);

    Rectangle<int> oscillator01FineTuneArea = oscillator01RightArea.removeFromTop(height / 2);
    prepareForSlider(true, m_margin, oscillator01FineTuneArea);
    oscillator01FineTuneArea.expand(0, m_margin * 0.25f);
    oscillator01FineTuneArea.removeFromTop(m_margin * 0.25f);
    m_osc01FineTuneSlider->setBounds(oscillator01FineTuneArea);
    
    Rectangle<int> oscillator01ModDepthArea = oscillator01RightArea.removeFromBottom(height / 2);
    prepareForSlider(true, m_margin, oscillator01ModDepthArea);
    m_osc01ModDepthSlider->setBounds(oscillator01ModDepthArea);

    // OSC 02
    Rectangle<int> oscillator02Area = canvas.removeFromRight(m_windowWidth * (6553.0f / 19200.0f));

    paramWidth = oscillator02Area.getWidth() / 3;

    Rectangle<int> oscillator02LeftArea = oscillator02Area.removeFromLeft(paramWidth);

    Rectangle<int> oscillator02RangeArea = oscillator02LeftArea.removeFromTop(height / 2);
    prepareForSlider(true, m_margin, oscillator02RangeArea);
    oscillator02RangeArea.expand(0, m_margin * 0.25f);
    oscillator02RangeArea.removeFromTop(m_margin * 0.25f);
    m_osc02RangeSlider->setBounds(oscillator02RangeArea);
    
    Rectangle<int> oscillator02ShapeArea = oscillator02LeftArea.removeFromBottom(height / 2);
    prepareForSlider(true, m_margin, oscillator02ShapeArea);
    m_osc02ShapeIntSlider->setBounds(oscillator02ShapeArea);

    Rectangle<int> oscillator02MiddleArea = oscillator02Area.removeFromLeft(paramWidth);

    Rectangle<int> oscillator02CoarseTuneArea = oscillator02MiddleArea.removeFromTop(height / 2);
    prepareForSlider(true, m_margin, oscillator02CoarseTuneArea);
    oscillator02CoarseTuneArea.expand(0, m_margin * 0.25f);
    oscillator02CoarseTuneArea.removeFromTop(m_margin * 0.25f);
    m_osc02CoarseTuneSlider->setBounds(oscillator02CoarseTuneArea);
    
    Rectangle<int> oscillator02ModSourceArea = oscillator02MiddleArea.removeFromBottom(height / 2);
    prepareForSlider(true, m_margin, oscillator02ModSourceArea);
    m_osc02ModSourceSlider->setBounds(oscillator02ModSourceArea);

    Rectangle<int> oscillator02RightArea = oscillator02Area.removeFromLeft(paramWidth);

    Rectangle<int> oscillator02FineTuneArea = oscillator02RightArea.removeFromTop(height / 2);
    prepareForSlider(true, m_margin, oscillator02FineTuneArea);
    oscillator02FineTuneArea.expand(0, m_margin * 0.25f);
    oscillator02FineTuneArea.removeFromTop(m_margin * 0.25f);
    m_osc02FineTuneSlider->setBounds(oscillator02FineTuneArea);
    
    Rectangle<int> oscillator02ModDepthArea = oscillator02RightArea.removeFromBottom(height / 2);
    prepareForSlider(true, m_margin, oscillator02ModDepthArea);
    m_osc02ModDepthSlider->setBounds(oscillator02ModDepthArea);

    // OSC SYNC
    canvas.expand(m_margin, m_margin);
    canvas.removeFromLeft(m_margin);
    canvas.removeFromTop(m_margin * 1.25f);

    m_oscSyncSlider->setBounds(canvas);
}
