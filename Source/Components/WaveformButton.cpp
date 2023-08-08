#include "WaveformButton.h"


WaveformButton::WaveformButton(const juce::String& buttonName)
    : juce::ShapeButton(
        buttonName,
        waveformButton_LookAndFeel.getNormalButtonColour(),
        waveformButton_LookAndFeel.getOverButtonColour(),
        waveformButton_LookAndFeel.getDownButtonColour()
    )
{
    this->setLookAndFeel(&waveformButton_LookAndFeel);
}

WaveformButton::~WaveformButton()
{
    setLookAndFeel(nullptr);
}


void WaveformButton::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    /** Draw button background. */
    waveformButton_LookAndFeel.drawButtonBackground(g, *this, waveformButton_LookAndFeel.getButtonBackgroundColour(),
        shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    /** Draw the button body */
    waveformButton_LookAndFeel.drawButtonBody(g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    /** Draw the waveform shape */
    waveformButton_LookAndFeel.drawWaveformShape(g, waveformButton_LookAndFeel.Sawtooth,
        this->getLocalBounds(), shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}
