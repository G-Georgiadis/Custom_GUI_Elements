#pragma once

#include "JuceHeader.h"

using namespace juce;

class WaveformButton_LookAndFeel : public juce::LookAndFeel_V4
{
public:
	enum Waveform
	{
		Sawtooth,
		Pulse,
		Triangle,
		Sinewave,
		Noise
	};

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
	{
		g.fillAll(backgroundColour);
	}

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

		if (/*!shouldDrawButtonAsHighlighted && */!shouldDrawButtonAsDown)
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
			break;
		}
	}


#pragma region Waveform
private:
	Waveform waveform;
public:
	void setWaveform(Waveform newWaveform)
	{
		waveform = newWaveform;
	}

	Waveform getWaveform()
	{
		return waveform;
	}
#pragma endregion


#pragma region Colour getters & setters
public:
	Colour getButtonBackgroundColour() { return buttonBackgroundColour;	}
	Colour getNormalButtonColour() { return normalButtonColour; }
	Colour getOverButtonColour() { return overbuttonColour; }
	Colour getDownButtonColour() { return downButonColour; }

	void setButtonBackgroundColour(Colour& newColour) { buttonBackgroundColour = newColour; }
	void setNormalButtonColour(Colour& newColour) { normalButtonColour = newColour; }
	void setOverButtonColour(Colour& newColour) { overbuttonColour = newColour; }
	void setDownButtonColour(Colour& newColour) { downButonColour = newColour; }
#pragma endregion



private:
	/** Background colour */
	Colour buttonBackgroundColour = Colours::transparentBlack;
	
	/** Button colours */
	Colour normalButtonColour = Colours::black.brighter(0.2);
	Colour overbuttonColour = Colours::black.brighter(0.2);
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

	Path noisePath;


	Random random;
};
