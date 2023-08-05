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
class Slider_MixingConsoleStyle_LookAndFeel : public juce::LookAndFeel_V4
{
public:
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
		/** Slider value range */
		slider.setRange(juce::Range<double>(0, 1), 0.01);

		/** Background. */
		drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);

		/** Outline. */
		drawLinearSliderOutline(g, x, y, width, height, sliderStyle, slider);

		/** Draw the rest of the slider elements that are orientation-specific */
		drawSliderElements(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);
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
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider)
	{
		g.setColour(outlineColour);
		outlinedRectangle = juce::Rectangle(x, y, width, height);
		g.drawRoundedRectangle(outlinedRectangle.toFloat(), outlineCornerSize, lineThickness);
	}

	/** Draws the track of the slider */
	void drawLinearSliderTrack(juce::Graphics& g, int x, int y, int width, int height,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider)
	{
		/** The horizontal center of the slider area (not including the taxt box if any) */
		const float sliderAreaCenterX = outlinedRectangle.getCentreX();
		/** The vertical center of the slider area (not including the taxt box if any) */
		const float sliderAreaCenterY = outlinedRectangle.getCentreY();

		const float sliderTrackCenterX = outlinedRectangle.getWidth() / 3.f;
		const float sliderTrackCenterY = outlinedRectangle.getHeight() / 3.f;

		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{	//Draw the slider track vertically
			/** Slider track */
			trackWidth = width * 0.125f;	// 1/8 of slider area width
			trackHeight = height * 0.8f;	// 4/5 of slider are height
			trackStartX = sliderTrackCenterX - trackWidth / 2.f;		// Slider area start x + center - half the width of the track
			trackEndX = trackStartX + trackWidth;
			trackStartY = sliderAreaCenterY - trackHeight / 2.f;	// Slider area start Y + center - half the heigght of the track
			trackEndY = trackStartY + trackHeight;

			/** Colour gradients */
			juce::Colour sliderTrackSides = juce::Colours::darkgrey.darker(0.7f);
			juce::Colour sliderTrackCenter = juce::Colours::black;
			juce::ColourGradient vetricalSliderTrackGradient = juce::ColourGradient::horizontal(sliderTrackSides, trackStartX + trackWidth / 4, sliderTrackSides, trackEndX - trackWidth / 4);
			vetricalSliderTrackGradient.addColour(0.5, sliderTrackCenter);

			/** Fill slider track with gradient */
			g.setGradientFill(vetricalSliderTrackGradient);
			/** Draw the slider track */
			g.fillRoundedRectangle(trackStartX, trackStartY, trackWidth, trackHeight, outlineCornerSize);
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{	//Draw the slider track horizontally
			/** Slider track */
			trackWidth = width * 0.8f;	// 4/5 of slider area width
			trackHeight = height * 0.125;	// 1/8 of slider are height
			trackStartX = sliderAreaCenterX - trackWidth / 2.f;		// Slider area start x + center - half the width of the track
			trackEndX = trackStartX + trackWidth;
			trackStartY = sliderTrackCenterY - trackHeight / 2.f;	// Slider area start Y + center - half the heigght of the track
			trackEndY = trackStartY + trackHeight;

			/** Colour gradients */
			juce::Colour sliderTrackSides = juce::Colours::darkgrey.darker(0.7f);
			juce::Colour sliderTrackCenter = juce::Colours::black;
			juce::ColourGradient horizontalSliderTrackGradient = juce::ColourGradient::vertical(sliderTrackSides, trackStartY + trackHeight / 4, sliderTrackSides, trackEndY - trackHeight / 4);
			horizontalSliderTrackGradient.addColour(0.5, sliderTrackCenter);

			/** Fill slider track with gradient */
			g.setGradientFill(horizontalSliderTrackGradient);

			/** Draw the slider track */
			g.fillRoundedRectangle(trackStartX, trackStartY, trackWidth, trackHeight, outlineCornerSize);
		}
	}

	/** Draws the slider thumb (slider cap) */
	void drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
	{
		const float sliderCapCornerSize = 5;
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
				width / 3.f - sliderCapWidth / 2.f,	// StartX
				sliderPos - sliderCapHeight / 2.f,
				sliderCapWidth,
				sliderCapHeight,
				sliderCapCornerSize);
			g.setColour(sliderCapColour);
			g.fillPath(sliderCap);

			juce::Rectangle<float> sliderCapCenterLine(
				width / 3.f - sliderCapWidth / 2.f,
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
				height / 3.f - sliderCapHeight / 2.f,
				sliderCapWidth,
				sliderCapHeight,
				sliderCapCornerSize);
			g.setColour(sliderCapColour);
			g.fillPath(sliderCap);

			juce::Rectangle<float> sliderCapCenterLine(
				sliderPos - 2,
				height / 3.f - sliderCapHeight / 2.f,
				5,
				sliderCapHeight);
			g.setColour(sliderCapCenterLineColour);
			g.fillRect(sliderCapCenterLine);
		}
	}

	void drawLinearSliderGrading(juce::Graphics& g, int x, int y, int width, int height, const juce::Slider::SliderStyle sliderStyle)
	{
		juce::Path grading;

		if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
		{
			/** The long line that runs paraller to the slider track */
			float longLineX = width * 5.f / 6.f;
			juce::Line longLine = juce::Line(longLineX, trackStartY, longLineX, trackEndY);
			grading.addLineSegment(longLine, 1);

			/** The smaller grading lines */
			float smallLineSize = width / 10.f;
			float smallLineDistance = (trackEndY - trackStartY) / 8.f;
			int gradingNumber = 10;

			for (int i = 0; i <= 8; i++)
			{
				juce::Point start = juce::Point(longLineX - smallLineSize, trackStartY + i * smallLineDistance);
				juce::Point end = juce::Point(longLineX, trackStartY + i * smallLineDistance);

				juce::Line line = juce::Line(start, end);

				grading.addLineSegment(line, 1);

				g.setColour(juce::Colours::beige.darker(0.5));
				g.setFont(juce::Font(10));

				g.drawText(juce::String(gradingNumber),
					longLineX - 2 * smallLineSize - 15,
					trackStartY + i * smallLineDistance - 15,
					30.f,
					30.f,
					juce::Justification::centred,
					true
				);
				gradingNumber -= 10;
			}
		}
		else if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
		{
			/** The long line that runs paraller to the slider track */
			float longLineY = height * 5.f / 6.f;
			juce::Line longLine = juce::Line(trackStartX, longLineY, trackEndX, longLineY);
			grading.addLineSegment(longLine, 1);

			/** The smaller grading lines */
			float smallLineSize = height / 10.f;
			float smallLineDistance = (trackEndX - trackStartX) / 8.f;
			int gradingNumber = 10;

			for (int i = 0; i <= 8; i++)
			{
				juce::Point start = juce::Point(trackEndX - i * smallLineDistance, longLineY);
				juce::Point end = juce::Point(trackEndX - i * smallLineDistance, longLineY - smallLineSize);

				juce::Line line = juce::Line(start, end);
				grading.addLineSegment(line, 1);


				g.setColour(juce::Colours::beige.darker(0.5));
				g.setFont(juce::Font(10));

				g.drawText(juce::String(gradingNumber),
					trackEndX - (i * smallLineDistance) - 15,
					longLineY - 2 * smallLineSize - 15,
					30.f,
					30.f,
					juce::Justification::centred,
					true
				);
				gradingNumber -= 10;
			}
		}

		g.setColour(juce::Colours::beige.darker(0.5));
		g.fillPath(grading);
	}

	/** Sets the slider style and calls the methods that draw the elements of the slider */
	void drawSliderElements(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider)
	{
		if (width > height)
		{
			slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		}
		else
		{
			slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		}
		

		/** Slider track */
		drawLinearSliderTrack(g, x, y, width, height, sliderStyle, slider);

		/** Slider cap (thumb) */
		drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos,
			maxSliderPos, sliderStyle, slider);

		drawLinearSliderGrading(g, x, y, width, height, sliderStyle);
	}

	/** Slider text box */
#pragma region Slider text box
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

#pragma endregion

	/** Colour getters and setters */
#pragma region Colour getters and setters
	/** Background colour */
	void setBackgroundColour(juce::Colour newColour)
	{
		backgroundColour = newColour;
	}

	juce::Colour getBackgroundColour()
	{
		return backgroundColour;
	}

	/** Outline colour */
	void setOutlineColour(juce::Colour newColour)
	{
		outlineColour = newColour;
	}

	juce::Colour getOutlineColour()
	{
		return outlineColour;
	}

	/** Slider cap colour */
	void setSliderCapColour(juce::Colour newColour)
	{
		sliderCapColour = newColour;
	}

	juce::Colour getSliderCapColour()
	{
		return sliderCapColour;
	}

	/** Slider cap line colour */
	void setSliderCapLineColour(juce::Colour newColour)
	{
		sliderCapCenterLineColour = newColour;
	}

	juce::Colour getSliderCapLineColour()
	{
		return sliderCapCenterLineColour;
	}

#pragma endregion


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
	const float outlineCornerSize = 10;
	const float lineThickness = 1.f;
	static const int numberOfDecimalPlaces = 2;
};
