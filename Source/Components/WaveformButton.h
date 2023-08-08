#pragma once


#include "JuceHeader.h"
#include "..\LookAndFeels\WaveformButton_LookAndFeel.h"


using namespace juce;


class WaveformButton : public ShapeButton
{
public:
	WaveformButton(const juce::String& buttonName);
	~WaveformButton() override;

	void paintButton(Graphics& g,
		bool shouldDrawButtonAsHighlighted,
		bool shouldDrawButtonAsDown) override;

	void setWaveform(WaveformButton_LookAndFeel::Waveform newWaveform);

	WaveformButton_LookAndFeel::Waveform getWaveform();
private:
	WaveformButton_LookAndFeel waveformButton_LookAndFeel;
	
	float toggleButtonCornerSize = 10.f;
};
