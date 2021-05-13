/*
  ==============================================================================

    PhantomLookAndFeel.h
    Created: 05 May 2021 16:15:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLookAndFeel.h"

#include "../utils/PhantomData.h"

void PhantomLookAndFeel::drawRotarySlider(
    Graphics& g,
    int x, int y,
    int width, int height,
    float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
    Slider& s
)
{
    const float radius = (jmin(width / 2, height / 2) - 2.0f) * 0.75f;
	const float centerX = x + width * 0.5f;
	const float centerY = y + height * 0.5f;
	const float rx = centerX - radius;
	const float ry = centerY - radius;
	const float rw = radius * 2.0f;

    if(sliderPos == 0.0f)
        sliderPos = 0.01f;

    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    StringArray nameTokens = StringArray::fromTokens(s.getName(), "_", "");
    String readout = getSliderReadout(s, nameTokens);

    const bool usePrimaryColour = nameTokens[0].equalsIgnoreCase("PRI");
    g.setColour(usePrimaryColour ? Consts::_PRIMARY_COLOUR : Consts::_SECONDARY_COLOUR);

    g.setFont(getFont());
    g.drawText(readout, centerX - radius, centerY - (m_fontSize * 5.0f / 12.0f), rw, m_fontSize, Justification::centred);

	Path arcPathFilled;
	arcPathFilled.addArc(rx, ry, rw, rw, rotaryStartAngle, angle, true);
	PathStrokeType(3.0f).createStrokedPath(arcPathFilled, arcPathFilled);
	g.fillPath(arcPathFilled);
}

Font PhantomLookAndFeel::getTextButtonFont(TextButton& tb, int buttonHeight)
{
    return getFont(m_fontSize * 1.3f);
}

void PhantomLookAndFeel::setFontSize(int windowWidth)
{
    m_fontSize = (float) windowWidth * _FONT_PER_WIDTH;
}

void PhantomLookAndFeel::setStrokeWidth(int windowWidth)
{
    m_strokeWidth = (float) windowWidth * _STROKE_PER_WIDTH;
}

String PhantomLookAndFeel::getSliderReadout(Slider& slider, StringArray& nameTokens)
{   
    String readout;

    if(nameTokens[3].equalsIgnoreCase("RANGE") && nameTokens[1].equalsIgnoreCase("OSC"))
    {
        readout = String(std::exp2f(3 - ((int) slider.getValue()) + 1)) + slider.getTextValueSuffix();
    }
    else if(nameTokens[3].equalsIgnoreCase("SHAPE") && nameTokens[1].equalsIgnoreCase("PHASOR"))
    {
        switch((int) slider.getValue())
        {
            default:
            case 0:
                readout = "SAW";
                break;

            case 1:
                readout = "TRI";
                break;
        }
    }
    else if(nameTokens[2].equalsIgnoreCase("MODE") && nameTokens[1].equalsIgnoreCase("FILTER"))
    {
        switch((int) slider.getValue())
        {
            default:
            case 0:
                readout = "LPF";
                break;

            case 1:
                readout = "BPF";
                break;
            
            case 2:
                readout = "HPF";
                break;
        }
    }
    else if(nameTokens[3].equalsIgnoreCase("SHAPE") && nameTokens[1].equalsIgnoreCase("LFO"))
    {
        switch((int) slider.getValue())
        {
            default:
            case 0:
                readout = "SINE";
                break;
            
            case 1:
                readout = "TRI";
                break;

            case 2:
                readout = "SAW";
                break;
            
            case 3:
                readout = "SQR";
                break;

            case 4:
                readout = "S+H";
                break;
        }
    }
    else if(nameTokens[2].equalsIgnoreCase("CUTOFF") && nameTokens[1].equalsIgnoreCase("FILTER"))
    {
        const float value = slider.getValue();
	    readout = (value >= 1000.0 ? String(value / 1000.0, 1) + "k" : String(value, 1));
    }
    else
    {
        readout = String(slider.getValue()) + slider.getTextValueSuffix();
    }

    return readout;
}

Font PhantomLookAndFeel::getFont() const
{
    return getFont(m_fontSize * 1.2f);
}

Font PhantomLookAndFeel::getFont(float fontSize) const
{
    Font f(Font(Typeface::createSystemTypefaceFor(
        PhantomData::montserrat_ttf, PhantomData::montserrat_ttfSize
    )));

    f.setHeight(fontSize);

    return f;
}
