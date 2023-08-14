#pragma once

#include "JuceHeader.h"
#include "..\Shapes\Shapes.h"

using namespace juce;
/**
 * LookAndFeel class for waveform selections buttons.
 */
class WaveformButton_LookAndFeel : public juce::LookAndFeel_V4
{
public:
	/**
	 * Waveform enum.
	 */
	enum Waveform
	{
		Sawtooth,
		Pulse,
		Triangle,
		Sinewave,
		Noise
	};


#pragma region Draw methods
	/**
* Draws the button background.
*
* \param Graphics& g: Reference to a graphics context used for drawing a component or image.
* \param Button& button: Reference to the button to draw.
* \param Colour backgroundColour: The colour to fill the background with.
* \param Bool shouldDrawButtonAsHighlighted:True if the button should be draw.
* \param Bool shouldDrawButtonAsDown:True if the button should appeat pressed.
*/
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
	{
		g.fillAll(backgroundColour);
	}

	/**
	 * Draws the body of the button.
	 *
	 * \param Graphics& g: Reference to a graphics context used for drawing a component or image.
	 * \param Button& button: Reference to the button to draw.
	 * \param Bool shouldDrawButtonAsHighlighted:True if the button should be draw.
	 * \param Bool shouldDrawButtonAsDown:True if the button should appeat pressed.
	 */
	void drawButtonBody(Graphics& g, Button& button,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
	{
		auto localBounds = button.getLocalBounds();
		auto localX = localBounds.getX();
		auto localY = localBounds.getY();
		auto localWidth = localBounds.getWidth();
		auto localHeight = localBounds.getHeight();

		auto lightCenter = Point<float>(localX + localWidth * 0.8f, localY + localHeight * 0.2);

		auto darkPoint = Point<float>(localX + localWidth * 0.5f, localY + localHeight * 0.5f);

		if (!shouldDrawButtonAsDown)
		{//Normal state
			auto buttonBodyColourGradient = ColourGradient(normalButtonColour.brighter(0.2), lightCenter,
				normalButtonColour, darkPoint, true);

			g.setGradientFill(buttonBodyColourGradient);
			g.fillRoundedRectangle(localBounds.toFloat(), 5);
		}
		else
		{
			auto buttonBodyColourGradient = ColourGradient(downButonColour.brighter(0.3), lightCenter,
				downButonColour, darkPoint, true);

			g.setGradientFill(buttonBodyColourGradient);
			g.fillRoundedRectangle(localBounds.toFloat(), 5);
		}
	}

	/**
	 * Draws the shape of the given waveform.
	 *
	 * \param Graphics& g: A graphics context used for drawing a component or image.
	 * \param Waveform waveform: The waveform to draw.
	 * \param Rectangle localBounds:The space to draw the waveform in.
	 * \param Bool shouldDrawButtonAsHighlighted:True if the button should be drawn highlighted. Not currently used.
	 * \param Bool shouldDrawButtonAsDown:True if the button should appeat pressed.
	 */
	void drawWaveformShape(Graphics& g, Waveform waveform, Rectangle<int> localBounds, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
	{
		float strokeLineThickness = 2;
		PathStrokeType::JointStyle jointStyle = PathStrokeType::JointStyle();
		PathStrokeType strokeType(strokeLineThickness, jointStyle);

		g.setColour(Colours::darkorange);

		switch (this->waveform)
		{
		case Sawtooth:
		{
			g.strokePath(Shapes::getSawtoothPath(localBounds.toFloat()), strokeType);
			break;
		}
		case Pulse:
		{
			g.strokePath(Shapes::getPulsePath(localBounds.toFloat()), strokeType);
			break;
		}
		case Triangle:
		{
			g.strokePath(Shapes::getTrianglePath(localBounds.toFloat()), strokeType);
			break;
		}
		case Sinewave:
		{
			g.strokePath(Shapes::getSinewavePath(localBounds.toFloat()), strokeType);
			break;
		}
		case Noise:
		{
			g.strokePath(Shapes::getNoisePath(localBounds.toFloat()), strokeType);
			break;
		}
		default:
		{
			g.strokePath(Shapes::getSawtoothPath(localBounds.toFloat()), strokeType);
			break;
		}
		}
	}
#pragma endregion


#pragma region Waveform
private:
	/**
	 * Instance of waveform enum.
	 */
	Waveform waveform;
public:
	/**
	 * Sets the waveform to be drawn on this waveform button.
	 * 
	 * \param Waveform newWaveform: The waveform to set or change to.
	 */
	void setWaveform(Waveform newWaveform)
	{
		waveform = newWaveform;
	}

	/**
	 * Returns the waveform assigned to the waveform button.
	 * 
	 * \return Waveform: The waveform assigned to the waveform button.
	 */
	Waveform getWaveform()
	{
		return waveform;
	}
#pragma endregion


#pragma region Colour getters & setters
public:
	/**
	 * Returns the background colour of this waveform button.
	 * 
	 * \return The background colour of this waveform button.
	 */
	Colour getButtonBackgroundColour() { return buttonBackgroundColour;	}

	/**
	 * Returns the normal colour (when not pressed or mouse-overed) of this waveform button.
	 *
	 * \return The normal  colour of this waveform button.
	 */
	Colour getNormalButtonColour() { return normalButtonColour; }

	/**
	 * Returns the over colour (when mouse-overed) of this waveform button.
	 *
	 * \return The over colour of this waveform button.
	 */
	Colour getOverButtonColour() { return overbuttonColour; }

	/**
	 * Returns the down colour (when pressed) of this waveform button.
	 *
	 * \return The down  colour of this waveform button.
	 */
	Colour getDownButtonColour() { return downButonColour; }


	/**
	 * Sets the background colour for this waveform button.
	 * 
	 * \param Colour& newColour: The colour to change the background to
	 */
	void setButtonBackgroundColour(Colour& newColour) { buttonBackgroundColour = newColour; }

	/**
	 * Sets the normal colour (when not pressed or mouse-overed) for this waveform button.
	 *
	 * \param Colour& newColour: The colour to change the normal colour  to
	 */
	void setNormalButtonColour(Colour& newColour) { normalButtonColour = newColour; }

	/**
	 * Sets the over colour (when mouse-overed) for this waveform button.
	 *
	 * \param Colour& newColour: The colour to change the over colour to
	 */
	void setOverButtonColour(Colour& newColour) { overbuttonColour = newColour; }

	/**
	 * Sets the down colour (when pressed) for this waveform button.
	 *
	 * \param Colour& newColour: The colour to change the down colour to
	 */
	void setDownButtonColour(Colour& newColour) { downButonColour = newColour; }
#pragma endregion


private:
	/** Background colour */
	Colour buttonBackgroundColour = Colours::transparentBlack;
	
	/** Button colours */
	/** Normal button colour */
	Colour normalButtonColour = Colours::black.brighter(0.2);
	/** Over (when mouse-overring) button colour */
	Colour overbuttonColour = Colours::black.brighter(0.2);
	/** Down (when pressed) button colour */
	Colour downButonColour = Colours::black.brighter(0.6);

	
	/** The path of the shape for noise button. */
	Path noisePath;

	
};
