/*****************************************************************//**
 * \file   LookAndFeels.h
 * \brief  A linear slider for use on level controls.
 * The orientation is set automatically based on the width/height given.
 * Currently optimised for code readability because I'm still learning.
 * 
 * \author George Georgiadis
 * \date   August 2023
 *********************************************************************/
#pragma once


#include "JuceHeader.h"
/**
 * A linear slider for use on level controls.
 * The orientation is set automatically based on the width/height given.
 */
class LevelSlider01LookAndFeel : public juce::LookAndFeel_V4
{
public:
	void drawLinearSlider(juce::Graphics& g, int x, int y, int width,
		int height, float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
	{
		/** Slider value range */
		slider.setRange(juce::Range<double>(0, 1), 0.01);

		/** Background. */
		drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);

		/** Outline. */
		drawLinearSliderOutline(g, x, y, width, height, sliderStyle, slider);

		/** Figure out which orientation to use based on given width and height and draw the slider accordingly */
		// Horizontal slider
		if (width > height)
		{	
			slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);

			/** Slider track */
			drawLinearSliderTrack(g, x, y, width, height, sliderStyle, slider);

			/** Slider cap (thumb) */
			drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos,
				maxSliderPos, sliderStyle, slider);
		}
		// Vertical slider
		else
		{	// This is a vertical slider
			slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);

			/** Slider track */
			drawLinearSliderTrack(g, x, y, width, height, sliderStyle, slider);

			/** Slider cap (thumb) */
			drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos,
				maxSliderPos, sliderStyle, slider);	
		}		
	}


	/** Draws the background of sliders */
	void drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle style, juce::Slider& slider) override
	{
		g.setColour(backgroundColour);
		g.fillRect(x, y, width, height);
	}

	/** Draws the outline */
	void drawLinearSliderOutline(juce::Graphics& g, int	x, int y, int width, int height,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider)
	{
		g.setColour(outlineColour);
		outlinedRectangle = juce::Rectangle(x, y, width, height);
		//outlinedRectangle.toFloat().reduce(border, border);
		g.drawRoundedRectangle(outlinedRectangle.toFloat(), cornerSize, lineThickness);
	}

	/** Draws the track of the slider */
	void drawLinearSliderTrack(juce::Graphics& g, int x, int y, int width, int height,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider)
	{
		/** The horizontal center of the slider area (not including the taxt box if any) */
		const float sliderAreaCenterX = outlinedRectangle.getCentreX();
		/** The vertical center of the slider area (not including the taxt box if any) */
		const float sliderAreaCenterY = outlinedRectangle.getCentreY();

		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{	//Draw the slider track vertically
			/** Slider track */
			trackWidth = width * 0.125f;	// 1/8 of slider area width
			trackHeight = height * 0.8f;	// 4/5 of slider are height
			trackStartX = sliderAreaCenterX - trackWidth / 2.f;		// Slider area start x + center - half the width of the track
			trackEndX = trackStartX + trackWidth;
			trackStartY = sliderAreaCenterY - trackHeight / 2.f;	// Slider area start Y + center - half the heigght of the track
			trackEndY = trackStartY + trackHeight;

			/** Colour gradients */
			juce::Colour sliderTrackSides = juce::Colours::darkgrey.darker(0.7f);
			juce::Colour sliderTrackCenter = juce::Colours::black;
			juce::ColourGradient vetricalSliderTrackGradient = juce::ColourGradient::horizontal(sliderTrackSides, trackStartX + trackWidth / 4, sliderTrackSides, trackEndX - trackWidth / 4);
			vetricalSliderTrackGradient.addColour(0.5, sliderTrackCenter);

			//g.setColour(juce::Colours::grey);
			g.setGradientFill(vetricalSliderTrackGradient);
			/** Draw the slider track */
			g.fillRoundedRectangle(trackStartX, trackStartY, trackWidth, trackHeight, cornerSize);

//#ifdef _DEBUG
//			/** Max line */
//			juce::Path topLine;
//			topLine.addRectangle(x, trackStartY, width, 1);
//			g.setColour(juce::Colours::grey);
//			g.fillPath(topLine);
//
//			/** Min line */
//			juce::Path bottomLine;
//			bottomLine.addRectangle(x, trackEndY, width, 1);
//			g.setColour(juce::Colours::grey);
//			g.fillPath(bottomLine);
//#endif
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{	//Draw the slider track horizontally
			/** Slider track */
			trackWidth = width * 0.8f;	// 4/5 of slider area width
			trackHeight = height * 0.125;	// 1/8 of slider are height
			trackStartX = sliderAreaCenterX - trackWidth / 2.f;		// Slider area start x + center - half the width of the track
			trackEndX = trackStartX + trackWidth;
			trackStartY = sliderAreaCenterY - trackHeight / 2.f;	// Slider area start Y + center - half the heigght of the track
			trackEndY = trackStartY + trackHeight;

			/** Colour gradients */
			juce::Colour sliderTrackSides = juce::Colours::darkgrey.darker(0.7f);
			juce::Colour sliderTrackCenter = juce::Colours::black;
			juce::ColourGradient horizontalSliderTrackGradient = juce::ColourGradient::vertical(sliderTrackSides, trackStartY + trackHeight/ 4, sliderTrackSides, trackEndY - trackHeight / 4);
			horizontalSliderTrackGradient.addColour(0.5, sliderTrackCenter);

			g.setGradientFill(horizontalSliderTrackGradient);
			//g.setColour(juce::Colours::grey);
			/** Draw the slider track */
			g.fillRoundedRectangle(trackStartX, trackStartY, trackWidth, trackHeight, cornerSize);

//#ifdef _DEBUG
//			/** Max line */
//			juce::Path topLine;
//			topLine.addRectangle(trackStartX, y, 1, height);
//			g.setColour(juce::Colours::grey);
//			g.fillPath(topLine);
//
//			/** Min line */
//			juce::Path bottomLine;
//			bottomLine.addRectangle(trackStartX + trackWidth, y, 1, height);
//			g.setColour(juce::Colours::grey);
//			g.fillPath(bottomLine);
//#endif
		}
	}

	/** Draws the slider thumb (slider cap) */
	void drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle,juce::Slider& slider) override
	{
		/** SliderCap */
		juce::Path sliderCap;
		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{	//Draw the slider cap vertically
			const float sliderCapHeightToTotalHeightRatio = 0.1f;
			const float sliderCapHeight = height * sliderCapHeightToTotalHeightRatio;
			const float sliderCapWidth = trackWidth * 2;

			sliderPos = juce::jmap<float>(
				sliderPos,
				height,
				y,
				trackEndY,
				trackStartY
			);

			sliderCap.addRoundedRectangle(
				outlinedRectangle.getCentreX() - sliderCapWidth / 2.f,	// StartX = Center - slider cap width / 2
				sliderPos - sliderCapHeight / 2.f,
				sliderCapWidth,
				sliderCapHeight,
				cornerSize);
			g.setColour(juce::Colours::darkgrey);
			g.fillPath(sliderCap);

			juce::Rectangle<float> sliderCapCenterLine(
				x + width / 2.f - sliderCapWidth / 2.f,
				sliderPos - 2,
				sliderCapWidth,
				5);
			g.setColour(sliderCapCenterLineColour);
			g.fillRect(sliderCapCenterLine);
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{	//Draw the slider cap horizontally
			const float sliderCapWidthToTotalWidthRatio = 0.1f;
			const float sliderCapHeight = trackHeight * 2;
			const float sliderCapWidth = trackWidth * sliderCapWidthToTotalWidthRatio;

			sliderPos = juce::jmap<float>(
				sliderPos,
				x,
				width,
				trackStartX,
				trackEndX
			);

			sliderCap.addRoundedRectangle(
				sliderPos - sliderCapWidth / 2.f,
				outlinedRectangle.getCentreY() - sliderCapHeight / 2.f,
				sliderCapWidth,
				sliderCapHeight,
				cornerSize);
			g.setColour(juce::Colours::darkgrey);
			g.fillPath(sliderCap);

			juce::Rectangle<float> sliderCapCenterLine(
				sliderPos - 2,
				y + height / 2.f - sliderCapHeight / 2.f,
				5,
				sliderCapHeight);
			g.setColour(sliderCapCenterLineColour);
			g.fillRect(sliderCapCenterLine);
			}
	}


	juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override
	{
		juce::Rectangle localBounds = slider.getLocalBounds();

		
		/*juce::Rectangle<int> sliderBounds = localBounds.removeFromTop(localBounds.getHeight() * 11 / 12);
		juce::Rectangle<int> textBoxBounds = localBounds;*/

		juce::Slider::SliderLayout layout;

		layout.sliderBounds = localBounds.removeFromTop(localBounds.getHeight() * 11 / 12);
		layout.textBoxBounds = localBounds;

		return layout;
	}


	juce::Label* createSliderTextBox(juce::Slider& slider) override
	{
		/** Slider text box number of decimal places to display */
		slider.setNumDecimalPlacesToDisplay(numberOfDecimalPlaces);

		juce::Label* sliderTextBoxPtr = LookAndFeel_V4::createSliderTextBox(slider);

		sliderTextBoxPtr->setColour(juce::Label::textColourId, juce::Colours::beige);
		sliderTextBoxPtr->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
		sliderTextBoxPtr->setColour(juce::Label::outlineColourId, juce::Colours::transparentBlack);
		sliderTextBoxPtr->setColour(juce::Label::textWhenEditingColourId, juce::Colours::beige);
		sliderTextBoxPtr->setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::black);
		sliderTextBoxPtr->setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::beige);

		// ToDo: Fix text box justification when editing the value

		return sliderTextBoxPtr;
	} 

private:
	/** Colours */
	const juce::Colour backgroundColour = juce::Colours::transparentWhite;
	const juce::Colour outlineColour = juce::Colours::beige;
	const juce::Colour sliderCapCenterLineColour = juce::Colours::black;	

	

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
	const float cornerSize = 5;
	const float lineThickness = 1.f;
	static const int numberOfDecimalPlaces = 2;
};
