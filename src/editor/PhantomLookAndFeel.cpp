/*
  ==============================================================================

    PhantomLookAndFeel.h
    Created: 05 May 2021 16:15:34
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomLookAndFeel.h"

#include "../utils/PhantomData.h"

void PhantomLookAndFeel::drawPopupMenuBackground(
    Graphics& g,
    int width,
    int height
)
{
    Rectangle<int> area(0, 0, width, height);

    g.setColour(Consts::_WHITE_COLOUR);
    g.fillRoundedRectangle(area.toFloat().expanded(width * 1.4f), 4.0f);
}

void PhantomLookAndFeel::drawPopupMenuItem(
    Graphics& g,
    const Rectangle<int>& area,
    bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
    const String& text,
    const String& shortcutKeyText,
    const Drawable* icon,
    const Colour* textColour
)
{
    g.setColour(Consts::_BLACK_COLOUR);

    if(isSeparator)
    {
        Range<int> range = area.getHorizontalRange();
        g.drawHorizontalLine(area.getCentreY(), range.getStart(), range.getEnd());
    }
    else
    {
        if(isHighlighted)
            g.fillAll(Consts::_WHITE_COLOUR.withMultipliedBrightness(0.9f));

        if(!isActive)
            g.setColour(Consts::_WHITE_COLOUR.withMultipliedBrightness(0.7f));

        const float padding = getPadding() * 1.5f;
        const float halfPadding = padding * 0.5f;

        Font f = getFont(m_fontSize * 1.2f);
        g.setFont(f);

        Rectangle<int> padded(padding, 0, area.getWidth() - padding, area.getHeight());
        g.drawText(text, padded, Justification::left, true);

        if(hasSubMenu)
        {
            Path triangle;

            Point<int> p1(area.getRight() - padding, area.getCentreY());
            Point<int> p2(p1.getX() - halfPadding, p1.getY() - halfPadding * 0.5f);
            Point<int> p3(p1.getX() - halfPadding, p1.getY() + halfPadding * 0.5f);

            triangle.addTriangle(p1.toFloat(), p2.toFloat(), p3.toFloat());

            g.setColour(Consts::_WHITE_COLOUR.withMultipliedBrightness(0.2f));
            g.fillPath(triangle);

        }
    }
}

void PhantomLookAndFeel::drawPopupMenuSectionHeader(
    Graphics& g,
    const Rectangle<int>& area,
    const String& sectionName
)
{
    g.setColour(Consts::_BLACK_COLOUR);

    Font f = getFont(m_fontSize * 1.5f);
    f.setBold(true);
    g.setFont(f);

    const float padding = getPadding() * 0.8f;

    Rectangle<int> padded(padding, 0, area.getWidth() - padding, area.getHeight());
    g.drawText(sectionName, padded, Justification::left, true);
}

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

    StringArray nameTokens = StringArray::fromTokens(s.getName(), "_", "");

    String readout = getSliderReadout(s, nameTokens);

    const bool useInactiveColour = nameTokens[2].equalsIgnoreCase("SYNC") && s.getValue() < 0.5f;
    const bool usePrimaryColour = nameTokens[0].equalsIgnoreCase("PRI");
    g.setColour(useInactiveColour ? Consts::_INACTIVE_COLOUR : usePrimaryColour ? Consts::_PRIMARY_COLOUR : Consts::_SECONDARY_COLOUR);

    g.setFont(getFont());
    g.drawText(readout, centerX - radius, centerY - (m_fontSize * 5.0f / 12.0f), rw, m_fontSize, Justification::centred);

    if(std::abs(sliderPos) <= 0.01f)
        sliderPos = sliderPos < 0.0f ? -0.01f : 0.01f;

    if(nameTokens[2].equalsIgnoreCase("SYNC"))
        sliderPos = 1.0f;

    const bool isDepthSlider = nameTokens.contains("DEPTH");
    const float startAngle = isDepthSlider ? (rotaryEndAngle - rotaryStartAngle) * 0.5f + rotaryStartAngle : rotaryStartAngle;
    const float endAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	
    Path arcPathFilled;
	arcPathFilled.addArc(rx, ry, rw, rw, startAngle, endAngle, true);
	PathStrokeType(3.0f).createStrokedPath(arcPathFilled, arcPathFilled);
	g.fillPath(arcPathFilled);
}

void PhantomLookAndFeel::drawToggleButton(
    Graphics& g, ToggleButton& b, 
    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown
)
{
    /**
     * NOTE: This is empty for the purpose of having "button-like sliders" 
     * in the sense of functionality.
     */
}

void PhantomLookAndFeel::drawCornerResizer(
    Graphics& g,
    int width, int height,
    bool isMouseOver, bool isMouseDragging
)
{
    g.setColour ((isMouseOver || isMouseDragging)
        ? Consts::_INACTIVE_COLOUR : Consts::_BLACK_COLOUR);

    const float lineThickness = jmin(width, height) * 0.1f;

    for (float i = 0.0f; i < 1.0f; i += 0.3f)
        g.drawLine (
            width * i,
            height + 1.0f,
            width + 1.0f,
            height * i,
            lineThickness
        );
}

Font PhantomLookAndFeel::getPopupMenuFont()
{
    return getFont(m_fontSize);
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

    if(nameTokens[1].equalsIgnoreCase("OSC"))
    {
        if(nameTokens[2].equalsIgnoreCase("SYNC"))
            readout = "SYNC";

        else if(nameTokens[3].equalsIgnoreCase("RANGE"))
            readout = String(std::exp2f(3 - ((int) slider.getValue()) + 1)) + slider.getTextValueSuffix();

        else if(nameTokens[3].equalsIgnoreCase("MOD") && nameTokens[4].equalsIgnoreCase("SOURCE"))
            readout = String(slider.getValue() < 0.5f ? "EG" : "LFO"); 

        else
            readout = String(slider.getValue(), 2) + slider.getTextValueSuffix();
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
	    String readoutVal = (value >= 1000.0 ? String(value / 1000.0, 1) + " k" : String(value, 1));
        readout = readoutVal + slider.getTextValueSuffix().substring(1);
    }
    else
    {
        readout = String(slider.getValue(), 2) + slider.getTextValueSuffix();
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

float PhantomLookAndFeel::getPadding()
{
    return m_fontSize * 0.75f;
}
