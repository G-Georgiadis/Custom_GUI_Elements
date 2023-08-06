/*****************************************************************//**
 * \file   Slider_SynthBipolar_LookAndFeel.h
 * \brief  A bipolar slider (that goes both positive and negative).
 * This is a linear scale slider, so it's best used for mixing modulation signals.
 * 
 * \author George Georgiadis
 * \date   August 2023
 *********************************************************************/
#pragma once

#include "JuceHeader.h"

class Slider_SynthBipolar_LookAndFeel : public juce::LookAndFeel_V4
{
public:
	/** Determines the layout - th part where the slider and the textbox are drawn */
	juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override
	{
		if (slider.getSliderStyle() == juce::Slider::SliderStyle::LinearVertical)
		{
			juce::Rectangle localBounds = slider.getLocalBounds();

			juce::Slider::SliderLayout layout;

			layout.sliderBounds = localBounds.removeFromTop(localBounds.getHeight() * 11 / 12);
			layout.textBoxBounds = localBounds;

			return layout;
		}
		else if (slider.getSliderStyle() == juce::Slider::SliderStyle::LinearHorizontal)
		{
			juce::Rectangle localBounds = slider.getLocalBounds();

			juce::Slider::SliderLayout layout;

			layout.sliderBounds = localBounds.removeFromTop(localBounds.getHeight() * 9 / 12);
			layout.textBoxBounds = localBounds;

			return layout;
		}
	}

	void drawLinearSlider(juce::Graphics& g, int x, int y, int width,
		int height, float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
	{
		/** Slider orientation */
		setSliderOrientation(width, height, slider);
		
		/** Background. */
		drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);

		/** Outline. */
		drawLinearSliderOutline(g, x, y, width, height, sliderStyle, slider);

		/** Slider track */
		drawSliderTrack(g, x, y, width, height, sliderStyle, slider);

		/** Slider cap (thumb) */
		drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);

		/** Grading lines */
		drawGradingLines(g, x, y, width, height, sliderStyle);
	}

	/** Draws the background of sliders */
	void drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
	{
		g.setColour(backgroundColour);
		g.fillRect(x, y, width, height);
	}

	/** Draws the outline */
	void drawLinearSliderOutline(juce::Graphics& g, int	x, int y, int width, int height,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
	{
		g.setColour(outlineColour);
		outlinedRectangle = juce::Rectangle(x, y, width, height);
		g.drawRoundedRectangle(outlinedRectangle.toFloat(), outlineCornerSize, lineThickness);
	}

	/** Draws the track that the slider runs along */
	void drawSliderTrack(juce::Graphics& g, int	x, int y, int width, int height,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider)
	{
		/** Gradients colours */
		juce::Colour sliderTrackSides = juce::Colours::darkgrey.darker(0.7f);
		juce::Colour sliderTrackCenter = juce::Colours::black;

		if (sliderStyle == juce::Slider::LinearVertical)
		{
			/** Slider track */
			trackWidth = width * 0.2f;
			trackHeight = height * 0.8f;
			trackStartX = width / 3.f - trackWidth / 2.f;
			trackEndX = width / 3.f + trackWidth / 2.f;
			trackStartY = height / 2.f - trackHeight / 2.f;
			trackEndY = height / 2.f + trackHeight / 2.f;

			/** Vertical gradient */
			juce::ColourGradient vetricalSliderTrackGradient = juce::ColourGradient::horizontal(sliderTrackSides, trackStartX + trackWidth / 4, sliderTrackSides, trackEndX - trackWidth / 4);
			vetricalSliderTrackGradient.addColour(0.5, sliderTrackCenter);

			/** Fill slider track with gradient */
			g.setGradientFill(vetricalSliderTrackGradient);
			/** Draw the slider track */
			g.fillRoundedRectangle(trackStartX, trackStartY, trackWidth, trackHeight, outlineCornerSize);
		}
		else if (sliderStyle == juce::Slider::LinearHorizontal)
		{
			const float centerX = width / 2.f;
			const float centerY = height / 3.f;

			trackWidth = width * 0.8f;
			trackHeight = height * 0.2f;
			trackStartX = centerX - trackWidth / 2.f;
			trackEndX = centerX + trackWidth / 2.f;
			trackStartY = centerY - trackHeight / 2.f;
			trackEndY = centerY + trackHeight / 2.f;

			/** Horizontal gradient */
			juce::ColourGradient horizontalSliderTrackGradient = juce::ColourGradient::vertical(sliderTrackSides, trackStartY + trackHeight / 4, sliderTrackSides, trackEndY - trackHeight / 4);
			horizontalSliderTrackGradient.addColour(0.5, sliderTrackCenter);

			/** Fill slider track with gradient */
			g.setGradientFill(horizontalSliderTrackGradient);
			/** Draw the slider track */
			g.fillRoundedRectangle(trackStartX, trackStartY, trackWidth, trackHeight, outlineCornerSize);
		}
	}

	/** Draws the slider cap (thumb) */
	void drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
	{
		int sliderCapWidth;
		int sliderCapHeight;
		int sliderCapStartX;
		int sliderCapStartY;
		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{
			/** Slider cap position scalling */
			sliderPos = juce::jmap(sliderPos, (float)y, (float)height, trackStartY, trackEndY);

			/** Slider cap dimensions */
			sliderCapWidth = 2.f * trackWidth;
			sliderCapHeight = 0.8f * sliderCapWidth;
			sliderCapStartX = trackStartX - sliderCapWidth * 0.25;
			sliderCapStartY = sliderPos - sliderCapHeight / 2.f;
			
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{
			/** Slider cap position scalling */
			sliderPos = juce::jmap(sliderPos, (float)x, (float)width, trackStartX, trackEndX);

			/** Slider cap dimensions */
			sliderCapHeight = 2.f * trackHeight;
			sliderCapWidth = 0.8f * sliderCapHeight;
			sliderCapStartX = sliderPos - sliderCapWidth / 2.f;
			sliderCapStartY = trackStartY - sliderCapHeight * 0.25;
		}
		/** Slider cap path */
		drawSliderCapPath(g, sliderCapStartX, sliderCapStartY, sliderCapWidth,
			sliderCapHeight, sliderStyle);
	}

	/** Draws the path (shape) of the slider cap */
	void drawSliderCapPath(juce::Graphics& g, int sliderCapStartX, int sliderCapStartY,
		int sliderCapWidth, int sliderCapHeight, juce::Slider::SliderStyle sliderStyle)
	{
		juce::Path sliderCapShape;
		const int sliderCapCornerSize = 2;
		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{
			sliderCapShape.startNewSubPath(sliderCapStartX, sliderCapStartY);	//Top left corner
			sliderCapShape.lineTo(sliderCapStartX, sliderCapStartY + sliderCapHeight);	//Bottom left corner
			sliderCapShape.lineTo(sliderCapStartX + sliderCapWidth * 0.666f, sliderCapStartY + sliderCapHeight);	//Bottom right corner
			sliderCapShape.lineTo(sliderCapStartX + sliderCapWidth, sliderCapStartY + sliderCapHeight / 2.f);	//Middle right pointer (points to value)
			sliderCapShape.lineTo(sliderCapStartX + sliderCapWidth * 0.666f, sliderCapStartY);	//Top right corner
			sliderCapShape.closeSubPath();
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{
			sliderCapShape.startNewSubPath(sliderCapStartX, sliderCapStartY);	//Top left corner
			sliderCapShape.lineTo(sliderCapStartX, sliderCapStartY + sliderCapHeight * 0.666f);	//Middle left corner
			sliderCapShape.lineTo(sliderCapStartX + sliderCapWidth / 2.f, sliderCapStartY + sliderCapHeight);	//Bottom center pointer (points to value)
			sliderCapShape.lineTo(sliderCapStartX + sliderCapWidth, sliderCapStartY + sliderCapHeight * 0.666f);	//Middle right corner
			sliderCapShape.lineTo(sliderCapStartX + sliderCapWidth, sliderCapStartY);	//Top right corner
			sliderCapShape.closeSubPath();
		}
		sliderCapShape = sliderCapShape.createPathWithRoundedCorners(sliderCapCornerSize);

		g.setColour(sliderCapColour);
		g.fillPath(sliderCapShape);
	}

	/** Draws the grading lines */
	void drawGradingLines(juce::Graphics& g, int x, int y, int width, int height, juce::Slider::SliderStyle sliderStyle)
	{
		g.setColour(outlineColour);
		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{
			/** Long line */
			g.drawLine(width * 0.75f, trackStartY, width * 0.75f, trackEndY);

			/** Shorter lines */
			for (int i = 0; i < 5; i++)
			{
				g.drawLine(width * 0.75f, trackStartY + i * trackHeight / 4, width * 0.55f, trackStartY + i * trackHeight / 4);
			}
			for (int i = 0; i < 21; i++)
			{
				g.drawLine(width * 0.75f, trackStartY + i * trackHeight / 20, width * 0.6f, trackStartY + i * trackHeight / 20);
			}
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{
			/** Long line */
			g.drawLine(trackStartX, height * 0.75f, trackEndX, height * 0.75f);

			/** Shorter lines */
			for (int i = 0; i < 5; i++)
			{
				g.drawLine(trackStartX + i * trackWidth / 4, height * 0.75f, trackStartX + i * trackWidth / 4, height *  0.55f);
			}
			for (int i = 0; i < 21; i++)
			{
				g.drawLine(trackStartX + i * trackWidth / 20, height * 0.75f, trackStartX + i * trackWidth / 20, height * 0.6f);
			}
		}
	}

private:
	/** Colours */
	juce::Colour backgroundColour = juce::Colours::transparentWhite;
	juce::Colour outlineColour = juce::Colours::beige;
	juce::Colour sliderCapColour = juce::Colours::darkgrey;
	juce::Colour sliderCapCenterLineColour = juce::Colours::black;


	/** Outline */
	juce::Rectangle<int> outlinedRectangle;

	/** Slider Track */
	float trackWidth;
	float trackHeight;
	float trackStartX;
	float trackEndX;
	float trackStartY;
	float trackEndY;

	/** Generic */
	const float border = 2;
	const float outlineCornerSize = 5;
	const float lineThickness = 1.f;
	static const int numberOfDecimalPlaces = 2;


	void setSliderOrientation(int width,
		int height, juce::Slider& slider)
	{
		if (height >= width) slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		else slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	}
};

