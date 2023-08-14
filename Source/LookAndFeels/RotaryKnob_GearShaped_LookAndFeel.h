#pragma once


#include "JuceHeader.h"

using namespace juce;

class RotaryKnob_GearShaped_LookAndFeel : public LookAndFeel_V4
{
public:
	/**
	 * Defines the bounds for the slider and the text box.
	 * 
	 * \param slider A slider. Used to access it's bounds and derive the slider and text box areas.
	 * \return A Slider::SliderLayout
	 */
	Slider::SliderLayout getSliderLayout(Slider& slider) override
	{
		Slider::SliderLayout layout;

		Rectangle<int> localBounds = slider.getLocalBounds();
		layout.sliderBounds = localBounds.removeFromTop(localBounds.getHeight() * 0.75f);
		//localBounds.removeFromBottom(localBounds.getHeight() * 0.6f);	// Space between slider and textbox
		layout.textBoxBounds = localBounds.removeFromBottom(localBounds.getHeight() * 0.6f);

		return layout;
	}


	/**
	 * Draws the rotary slider.
	 * 
	 * \param g
	 * \param x
	 * \param y
	 * \param width
	 * \param height
	 * \param sliderPosProportional
	 * \param rotaryStartAngle
	 * \param rotaryEndAngle
	 * \param slider
	 */
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
	{
		constexpr int numberOfSides = 8;
		constexpr float numberOfRadiansPerSide = 2 * MathConstants<float>::pi / numberOfSides;

		/** Using the smallest dimension as the totalDiameter to ensure that the knob fits the bounds. */
		int totalDiameter = (width < height) ? width : height;
		float totalRadius = totalDiameter / 2.f;
		float totalCenterX = x + width / 2.f;
		float totalCenterY = y + height / 2.f;

		float angle = rotaryStartAngle + (sliderPosProportional * (rotaryEndAngle - rotaryStartAngle));

#ifdef DEBUG
		/** Helper circle - max within bounds */
		g.setColour(Colours::darkred);
		g.drawEllipse(
			(width < height) ? x : totalCenterX - totalRadius,
			(width < height) ? totalCenterY - totalRadius : y,
			totalDiameter,
			totalDiameter,
			1
		);
#endif // DEBUG

		/** Knob outer circle. The outer gear shape edges should touch this circle. */
		float knobGearOuterDiameter = 0.9f * totalDiameter;
		float knobGearOuterRadius = knobGearOuterDiameter / 2.f;

		/** Knob inner circle. The inner gear shape edges should touch this circle. */
		float knobGearInnerDiameter = 0.75 * totalDiameter;

		/****************************************************************************
		 * Disk at the bottom of the knob.
		 */
		 /** Base colour */
		g.setColour(Colours::black.brighter(0.03));
		g.fillEllipse
		(
			totalCenterX - knobGearOuterRadius,
			totalCenterY - knobGearOuterRadius,
			knobGearOuterDiameter,
			knobGearOuterDiameter
		);
		/** Light reflection. */
		ColourGradient backDiskGradient = ColourGradient(
			Colours::white.withAlpha(0.15f), totalCenterX + knobGearOuterRadius / 2.f, totalCenterY - knobGearOuterRadius,
			Colours::black.withAlpha(0.1f), totalCenterX - knobGearOuterRadius / 2.f, totalCenterY + knobGearOuterRadius,
			true);
		g.setGradientFill(backDiskGradient);
		g.fillEllipse
		(
			totalCenterX - knobGearOuterRadius,
			totalCenterY - knobGearOuterRadius,
			knobGearOuterDiameter,
			knobGearOuterDiameter
		);


		/****************************************************************************
		 * Pointer.
		 */
		Path knobPointerPath;
		knobPointerPath.startNewSubPath(totalCenterX, y + (totalDiameter - knobGearOuterDiameter) / 2.f);
		knobPointerPath.lineTo(totalCenterX + 0.15f * (knobGearOuterDiameter - knobGearInnerDiameter) / 2, y + (knobGearOuterDiameter - knobGearInnerDiameter));
		knobPointerPath.lineTo(totalCenterX - 0.15f * (knobGearOuterDiameter - knobGearInnerDiameter) / 2, y + (knobGearOuterDiameter - knobGearInnerDiameter));
		knobPointerPath.closeSubPath();
		knobPointerPath = knobPointerPath.createPathWithRoundedCorners(5.f);

		knobPointerPath.applyTransform(AffineTransform::rotation(
			angle,
			totalCenterX,
			totalCenterY)
		);

		g.setColour(Colours::beige.darker(0.8));
		g.fillPath(knobPointerPath);


		/****************************************************************************
		 * Gear shaped knob.
		 */
		Path gearShapedKnobPath = getGearShapedPath(numberOfSides, totalDiameter, totalCenterX, totalCenterY, knobGearInnerDiameter);
		
		/** Rotate the knob depending on value (angle) */
		gearShapedKnobPath.applyTransform(AffineTransform::rotation(
			angle,
			totalCenterX,
			totalCenterY));
		
		DropShadow gearShadow = DropShadow(juce::Colours::black.withAlpha(0.3f), 20, juce::Point(-10, 10));
		gearShadow.drawForPath(g, gearShapedKnobPath);
		
		/** Knob base colour */
		g.setColour(Colours::black.brighter(0.05));
		g.fillPath(gearShapedKnobPath);

		/** Gradient for light reflection effect. */
		ColourGradient gearTopGradient = ColourGradient(
			Colours::white.withAlpha(0.15f), totalCenterX + knobGearOuterRadius / 2.f, totalCenterY - knobGearOuterRadius,
			Colours::black.withAlpha(0.1f), totalCenterX - knobGearOuterRadius / 2.f, totalCenterY + knobGearOuterRadius,
			true);
		g.setGradientFill(gearTopGradient);
		g.fillPath(gearShapedKnobPath);
	}

	/** Draws the text box of the rotary knob. */
	Label* createSliderTextBox(Slider& slider) override
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
	static constexpr int numberOfDecimalPlaces = 2;
	
	/** Returns a gear shaped path */
	Path getGearShapedPath(int numberOfSides, float totalDiameter, float totalCenterX, float totalCenterY, float knobGearInnerDiameter)
	{
		Path gearShapedKnobPath;
		/** Circle to take an arc from */
		float radiusOfCircleToTakeArcFrom = 0.25f * totalDiameter;
		float circleToTakeArcFrom_CenterX = totalCenterX;
		float circleToTakeArcFrom_CenterY = totalCenterY - knobGearInnerDiameter;
		float circleToTakeArcFrom_Radius = knobGearInnerDiameter / 2.f;
		constexpr float eighthOfCircleRadians = MathConstants<float>::pi / 4.f;
		/** The gear shape will be created by drawing arcs, connecting them
		 * (to make the outer flat bits) and then filling the inside. */
		for (int i = 0; i < numberOfSides; i++)
		{
			bool beginNewSubpath = (i == 0) ? true : false;	// New path for the 1st arc only so that the rest are connected.
			gearShapedKnobPath.addCentredArc(
				circleToTakeArcFrom_CenterX,	//centerX
				circleToTakeArcFrom_CenterY,	//centerY
				circleToTakeArcFrom_Radius,	//radiusX
				circleToTakeArcFrom_Radius,	//radiusY
				0,	// Angle by which the whole ellipse should be rotated about its centre, in radians (clockwise)
				3.5f * eighthOfCircleRadians,	// From radians
				4.5f * eighthOfCircleRadians,	// To radians
				beginNewSubpath);
			gearShapedKnobPath.applyTransform(AffineTransform::rotation(eighthOfCircleRadians, totalCenterX, totalCenterY));
		}
		gearShapedKnobPath.closeSubPath();

		return gearShapedKnobPath;
	}
};
