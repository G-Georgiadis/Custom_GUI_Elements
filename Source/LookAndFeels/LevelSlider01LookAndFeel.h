/*****************************************************************//**
 * \file   LookAndFeels.h
 * \brief  A set of custom UI Elelments
 * 
 * \author George Georgiadis
 * \date   August 2023
 *********************************************************************/
#pragma once


#include "JuceHeader.h"

class LevelSlider01LookAndFeel : public juce::LookAndFeel_V4
{
public:
	void drawLinearSlider
	(
		juce::Graphics& g,
		int x,
		int y,
		int width,
		int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle,
		juce::Slider& slider
	) override
	{
		/** Background */
		drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);

		/** Outline */
		drawLinearSliderOutline(g, x, y, width, height, sliderStyle, slider);


		/** Track. The proportions are taken from the schematic https://gr.mouser.com/datasheet/2/414/TTRB_S_A0009241322_1-2565559.pdf */
		const float trackStartX = x + width - (width * 9.f / 16.f);
		const float trackStartY = y + (height - (height * 100.f / 128.f)) / 2.f;
		const float trackWidth = width * 2.f / 16.f;
		const float trackHeight = height * 100.f / 128.f;

		juce::Rectangle<float> track(trackStartX, trackStartY, trackWidth, trackHeight);

		g.setColour(juce::Colours::grey);
		g.fillRect(track);

		/** Slider cap (thumb) */
		drawLinearSliderThumb(
			g,
			x,
			y,
			width,
			height,
			sliderPos,
			minSliderPos,
			maxSliderPos,
			sliderStyle,
			slider);


		/** Max line */
		juce::Path topLine;
		topLine.addRectangle(x, trackStartY, width, 1);
		g.setColour(juce::Colours::grey);
		g.fillPath(topLine);

		/** Min line */
		juce::Path bottomLine;
		bottomLine.addRectangle(x, trackStartY + trackHeight, width, 1);
		g.setColour(juce::Colours::grey);
		g.fillPath(bottomLine);
	}

	/** Draws the background of sliders */
	void drawLinearSliderBackground(
		juce::Graphics& g,
		int x,
		int y,
		int width,
		int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const juce::Slider::SliderStyle style,
		juce::Slider& slider) override
	{
		g.setColour(backgroundColour);
		g.fillRect(x, y, width, height);
	}


	void drawLinearSliderOutline(
		juce::Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		const juce::Slider::SliderStyle sliderStyle,
		juce::Slider& slider
	)
	{
		g.setColour(outlineColour);
		juce::Rectangle outlinedRectangle(x, y, width, height);
		outlinedRectangle.reduce(border, border);
		g.drawRoundedRectangle(outlinedRectangle.toFloat(), cornerSize, lineThickness);
	}


	/** Draws the slider thumb (slider cap) */
	void drawLinearSliderThumb(
		juce::Graphics& g,
		int x,
		int y,
		int width,
		int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const juce::Slider::SliderStyle,
		juce::Slider&) override
	{
		/** SliderCap */
		juce::Path sliderCap;

		/**
		 * The slider cap dimensions (width:height) are 1:2.
		 * The slider cap width to the width of the control is 16:12.
		 */

		const float sliderCapWidthToTotalWidthRatio = 12.f / 16.f;
		const float sliderCapWidth = width * sliderCapWidthToTotalWidthRatio;

		const float trackStartY = y + (height - (height * 100.f / 128.f)) / 2.f;
		const float trackHeight = height * 100.f / 128.f;

		sliderPos = juce::jmap<float>(
			sliderPos,	//sourceValue
			height,		//sourceRangeMin
			y,			//sourceRangeMax
			trackStartY + trackHeight - (height - trackHeight) / 8.f,		//targetRangeMin
			trackStartY								//targetRangeMax 
		);

		sliderCap.addRoundedRectangle(
			x + width / 2.f - sliderCapWidth / 2.f,
			sliderPos - sliderCapWidth,
			sliderCapWidth,
			sliderCapWidth * 2,
			cornerSize);
		g.setColour(juce::Colours::grey);
		g.fillPath(sliderCap);


		/** SliderCap center line */
		juce::Rectangle<float> sliderCapCenterLine(
			x + width / 2.f - sliderCapWidth / 2.f,
			sliderPos - sliderCapWidth * 2 /48.f,
			sliderCapWidth,
			sliderCapWidth * 2 / 24.f);
		g.setColour(sliderCapCenterLineColour);
		g.fillRect(sliderCapCenterLine);
	}

private:
	const juce::Colour backgroundColour = juce::Colours::black;
	const juce::Colour outlineColour = juce::Colours::beige;
	const juce::Colour sliderCapCenterLineColour = juce::Colours::black;
	const float border = 2;
	const float cornerSize = 5;
	const float lineThickness = 1.f;
};
