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
		if (waveform == Sawtooth)
		{
			float strokeLineThickness = 2;
			PathStrokeType::JointStyle jointStyle = PathStrokeType::JointStyle();
			PathStrokeType strokeType(strokeLineThickness, jointStyle);

			g.setColour(Colours::darkorange);
			g.strokePath(getSawtoothPath(localBounds.toFloat()), strokeType);
		}
	}


#pragma region Waveform
	void setWaveform(Waveform newWaveform)
	{
		this->waveform = newWaveform;
	}

	Waveform getWaveform()
	{
		return waveform;
	}
#pragma endregion


#pragma region Colour getters & setters
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


	Path pulsePath;
	Path trianglePath;
	Path sinewavePath;
	Path noisePath;

	Waveform waveform;
};
