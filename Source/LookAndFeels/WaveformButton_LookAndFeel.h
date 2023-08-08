#pragma once

#include "JuceHeader.h"

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
			g.strokePath(getSawtoothPath(localBounds.toFloat()), strokeType);
			break;
		}
		case Pulse:
		{
			g.strokePath(getPulsePath(localBounds.toFloat()), strokeType);
			break;
		}
		case Triangle:
		{
			g.strokePath(getTrianglePath(localBounds.toFloat()), strokeType);
			break;
		}
		case Sinewave:
		{
			g.strokePath(getSinewavePath(localBounds.toFloat()), strokeType);
			break;
		}
		case Noise:
		{
			g.strokePath(getNoisePath(localBounds.toFloat()), strokeType);
			break;
		}
		default:
		{
			g.strokePath(getSawtoothPath(localBounds.toFloat()), strokeType);
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

	/** Shapes */
	/** Returns a sawtooth shaped Path */
	Path getSawtoothPath(Rectangle<float>&& buttonBounds)
	{
		buttonBounds.reduced(6, 6);

		/** Bounds dimensions. */
		float boundsX = buttonBounds.getX();
		float boundsY = buttonBounds.getY();
		float boundsWidth = buttonBounds.getWidth();
		float boundsHeight = buttonBounds.getHeight();

		//float buttonSide

		/** Button X and Y centers */
		float centerX = boundsWidth / 2.f;
		float centerY = boundsHeight / 2.f;

		auto sawtoothPath = Path();

		/** Design the sawtooth path. */
		sawtoothPath.startNewSubPath(centerX - centerY, boundsY + centerY);
		sawtoothPath.lineTo(centerX, boundsY + boundsHeight * 0.2f);
		sawtoothPath.lineTo(centerX, boundsY + boundsHeight * 0.8f);
		sawtoothPath.lineTo(centerX + centerY, boundsY + centerY);

		return sawtoothPath;
	}

	/** Returns a pulse shaped Path */
	Path getPulsePath(Rectangle<float>&& buttonBounds)
	{
		buttonBounds.reduced(6, 6);

		/** Bounds dimensions. */
		float boundsX = buttonBounds.getX();
		float boundsY = buttonBounds.getY();
		float boundsWidth = buttonBounds.getWidth();
		float boundsHeight = buttonBounds.getHeight();

		//float buttonSide

		/** Button X and Y centers */
		float centerX = boundsWidth / 2.f;
		float centerY = boundsHeight / 2.f;

		auto pulsePath = Path();

		/** Design the pulse path. */
		pulsePath.startNewSubPath(centerX - centerY, boundsY + centerY);
		pulsePath.lineTo(centerX - centerY, boundsY + boundsHeight * 0.2f);	//Up
		pulsePath.lineTo(centerX - centerY / 3.f, boundsY + boundsHeight * 0.2f);	//Right
		pulsePath.lineTo(centerX - centerY / 3.f, boundsY + boundsHeight * 0.8f);	//Down
		pulsePath.lineTo(centerX + centerY, boundsY + boundsHeight * 0.8f);	//Right
		pulsePath.lineTo(centerX + centerY, boundsY + boundsHeight / 2.f);	//Up


		return pulsePath;
	}

	/** Returns a triangle shaped Path */
	Path getTrianglePath(Rectangle<float>&& buttonBounds)
	{
		buttonBounds.reduced(6, 6);

		/** Bounds dimensions. */
		float boundsX = buttonBounds.getX();
		float boundsY = buttonBounds.getY();
		float boundsWidth = buttonBounds.getWidth();
		float boundsHeight = buttonBounds.getHeight();

		//float buttonSide

		/** Button X and Y centers */
		float centerX = boundsWidth / 2.f;
		float centerY = boundsHeight / 2.f;

		auto trianglePath = Path();

		/** Design the triangle path. */
		trianglePath.startNewSubPath(centerX - centerY, boundsY + centerY);
		trianglePath.lineTo(centerX - centerY / 2.f, boundsY + boundsHeight * 0.2f);	//Up-Rigth
		trianglePath.lineTo(centerX, centerY);	//Center
		trianglePath.lineTo(centerX + centerY / 2.f, boundsY + boundsHeight * 0.8f);	//Down
		trianglePath.lineTo(centerX + centerY, boundsY + centerY);	//Up-Right
		


		return trianglePath;
	}

	/** Returns a sinewave shaped Path */
	Path getSinewavePath(Rectangle<float>&& buttonBounds)
	{
		buttonBounds.reduced(6, 6);

		/** Bounds dimensions. */
		float boundsX = buttonBounds.getX();
		float boundsY = buttonBounds.getY();
		float boundsWidth = buttonBounds.getWidth();
		float boundsHeight = buttonBounds.getHeight();

		//float buttonSide

		/** Button X and Y centers */
		float centerX = boundsWidth / 2.f;
		float centerY = boundsHeight / 2.f;

		auto sinewavePath = Path();

		/** Design the sinewave path. */
		sinewavePath.startNewSubPath(centerX - centerY, boundsY + centerY);
		sinewavePath.addArc(
			centerX - centerY,	// X
			boundsY + boundsHeight * 0.2f,	// Y
			boundsHeight / 2.f,
			boundsHeight * 0.6f,
			-0.5f * juce::float_Pi,
			0.5f * juce::float_Pi
		);
		sinewavePath.addArc(
			centerX,
			boundsY + boundsHeight * 0.2f,
			boundsHeight / 2.f,
			boundsHeight * 0.6f,
			-0.5f * juce::float_Pi,
			-1.5f * juce::float_Pi
		);



		return sinewavePath;
	}

	/** Returns a noise shaped Path */
	Path getNoisePath(Rectangle<float>&& buttonBounds)
	{
		if (noisePath.isEmpty())
		{
			buttonBounds.reduced(6, 6);

			/** Bounds dimensions. */
			float boundsX = buttonBounds.getX();
			float boundsY = buttonBounds.getY();
			float boundsWidth = buttonBounds.getWidth();
			float boundsHeight = buttonBounds.getHeight();

			//float buttonSide

			/** Button X and Y centers */
			float centerX = boundsWidth / 2.f;
			float centerY = boundsHeight / 2.f;
			float stepX = boundsWidth / 9.f;

			/** Design the noise path. */
			noisePath.startNewSubPath(centerX - centerY, boundsY + centerY);
			for (int i = 1; i < 6; i++)
			{
				noisePath.lineTo(centerX - centerY + stepX * i, boundsY + boundsHeight * 0.2f + random.nextFloat() * 0.6f * boundsHeight);
			}
			noisePath.lineTo(centerX + centerY, boundsY + centerY);

			return noisePath;
		}
		else return noisePath;
	}

	/** The path of the shape for noise button. */
	Path noisePath;

	/** Instance of Random. */
	Random random;
};
