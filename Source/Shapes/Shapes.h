/*
  ==============================================================================

    Shapes.h
    Created: 7 Apr 2023 7:25:12pm
    Author:  G

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
Class to make and store shapes used in the GUI
*/
class Shapes  : public Component
{
public:
    //Transport bar button shapes
    static Path getOpenButtonPath();
    static Path getSkipToStartButtonPath();
    static Path getRewindButtonPath();
    static Path getStopButtonPath();
    static Path getPlayButtonPath();
    static Path getPauseButtonPath();
    static Path getFastForwardButtonPath();
    static Path getSkipToEndButtonPath();

    //Waveform shapes
    static Path getSawtoothPath(Rectangle<float>&& buttonBounds);
    static Path getPulsePath(Rectangle<float>&& buttonBounds);
    static Path getTrianglePath(Rectangle<float>&& buttonBounds);
    static Path getSinewavePath(Rectangle<float>&& buttonBounds);
    static Path getNoisePath(Rectangle<float>&& buttonBounds);

    // Slider and knob shapes
    static Path getGearShapedPath(int numberOfSides, float totalDiameter, float totalCenterX, float totalCenterY, float knobGearInnerDiameter)
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
private:
    static const Rectangle<int> localBounds;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Shapes)
};
