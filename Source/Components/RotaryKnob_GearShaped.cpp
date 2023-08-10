#pragma once


#include "JuceHeader.h"
#include "RotaryKnob_GearShaped.h"


RotaryKnob_GearShaped::RotaryKnob_GearShaped()
{
	this->setLookAndFeel(&rotaryKnob_GearShaped_LookAndFeel);

	this->setSliderStyle(Slider::RotaryVerticalDrag);

}

RotaryKnob_GearShaped::~RotaryKnob_GearShaped()
{
	this->setLookAndFeel(nullptr);
}
