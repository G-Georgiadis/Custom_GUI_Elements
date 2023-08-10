#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
	: elementSelectorComboBox("elementSelectorComboBox"),
	slider01Vertical("slider01Vertical"),
	slider01Horizontal("slider01Horizontal"),
	slider02Vertical("slider02Vertical"),
	slider02Horizontal("slider02Horizontal"),
	sawtoothButton("sawtoothButton"),
	pulseButton("pulseButton"),
	triangleButton("triangleButton"),
	sinewaveButton("sinewaveButton"),
	noiseButton("noiseButton")
{
	addAndMakeVisible(elementSelectorComboBox);

	elementSelectorComboBox.addItem(juce::String("Mixing console style slider"), 1001);
	elementSelectorComboBox.addItem(juce::String("Synth bipolar slider"), 1002);
	elementSelectorComboBox.addItem(juce::String("Rotary gear-shaped knob"), 1003);
	elementSelectorComboBox.addItem(juce::String("Waveform buttons"), 1004);
	

	elementSelectorComboBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, slider_MixingConsoleStyle_LookAndFeel.getBackgroundColour());
	elementSelectorComboBox.setColour(juce::ComboBox::ColourIds::outlineColourId, slider_MixingConsoleStyle_LookAndFeel.getOutlineColour());

	elementSelectorComboBox.setSelectedItemIndex(2);

	elementSelectorComboBox.addListener(this);

	/** Mixing console style faders. */
	addChildComponent(slider01Vertical);
	addChildComponent(slider01Horizontal);
	/** Synth bipolar sliders. */
	addChildComponent(slider02Vertical);
	addChildComponent(slider02Horizontal);

	/** Set slider text box button positions and dimensions. */
	slider01Vertical.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
	slider01Horizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
	slider02Vertical.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
	slider02Horizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

	/** Assign LookAndFeel to sliders. */
	slider01Vertical.setLookAndFeel(&slider_MixingConsoleStyle_LookAndFeel);
	slider01Horizontal.setLookAndFeel(&slider_MixingConsoleStyle_LookAndFeel);
	slider02Vertical.setLookAndFeel(&slider_SynthBipolar_LookAndFeel);
	slider02Horizontal.setLookAndFeel(&slider_SynthBipolar_LookAndFeel);

	/** Set bipolar sliders range. */
	slider02Vertical.setRange(-1, 1, 0.01);
	slider02Horizontal.setRange(-1, 1, 0.01);


	/** Gear shaped rotary slider */
	addChildComponent(rotaryKnob_GearShaped);


	/** Sawtooth button */
	sawtoothButton.setWaveform(WaveformButton_LookAndFeel::Sawtooth);
	addChildComponent(sawtoothButton);

	/** Pulse button */
	pulseButton.setWaveform(WaveformButton_LookAndFeel::Pulse);
	addChildComponent(pulseButton);

	/** Trinagle button */
	triangleButton.setWaveform(WaveformButton_LookAndFeel::Triangle);
	addChildComponent(triangleButton);

	/** Sinewave button */
	sinewaveButton.setWaveform(WaveformButton_LookAndFeel::Sinewave);
	addChildComponent(sinewaveButton);

	/** Sinewave button */
	noiseButton.setWaveform(WaveformButton_LookAndFeel::Noise);
	addChildComponent(noiseButton);

	setSize(600, 400);
}

MainComponent::~MainComponent()
{
	slider01Vertical.setLookAndFeel(nullptr);
	slider01Horizontal.setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{

}

void MainComponent::resized()
{
	juce::Rectangle localBounds = getLocalBounds();
	elementSelectorComboBox.setBounds(localBounds.removeFromTop(30));
	localBounds.removeFromTop(10);

	rotaryKnob_GearShaped.setBounds(localBounds);

	/** Waveform buttons */
	for (int i = 0; i < 5; i++)
	{
		int buttonWidth = 30;
		int buttonHeight = 20;
		int buttonX = localBounds.getX();
		int buttonY = localBounds.getY() + i * (buttonHeight + 5);

		Rectangle buttonBounds = Rectangle<int>(buttonX, buttonY, buttonWidth, buttonHeight);
		switch (i)
		{
		case 0:
			sawtoothButton.setBounds(buttonBounds);
			break;
		case 1:
			pulseButton.setBounds(buttonBounds);
			break;
		case 2:
			triangleButton.setBounds(buttonBounds);
			break;
		case 3:
			sinewaveButton.setBounds(buttonBounds);
			break;
		case 4:
			noiseButton.setBounds(buttonBounds);
			break;
		default:
			break;
		}
	}


	auto verticalSliderBounds = localBounds.removeFromLeft(100);
	localBounds.removeFromLeft(10);
	auto horizontalSliderBounds = localBounds.removeFromBottom(140);

	slider01Vertical.setBounds(verticalSliderBounds);
	slider01Horizontal.setBounds(horizontalSliderBounds);


	slider02Vertical.setBounds(verticalSliderBounds);
	slider02Horizontal.setBounds(horizontalSliderBounds);

	//rotaryKnob_GearShaped.setBounds(10, 40, 100, 100);
}

void MainComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
	if (comboBoxThatHasChanged == &elementSelectorComboBox)
	{
		makeAllControlsInvisible();

		switch (comboBoxThatHasChanged->getSelectedItemIndex())
		{
		case 0: // Mixing console style slider
		{
			slider01Vertical.setVisible(true);
			slider01Horizontal.setVisible(true);
			break;

		}
		case 1: // Synth bipolar slider
		{
			slider02Vertical.setVisible(true);
			slider02Horizontal.setVisible(true);
			break;
		}
		case 2:// Rotary gear-shaped knob
		{
			rotaryKnob_GearShaped.setVisible(true);
			break;
		}
		case 3:	 //Waveform buttons
		{
			sawtoothButton.setVisible(true);
			pulseButton.setVisible(true);
			triangleButton.setVisible(true);
			sinewaveButton.setVisible(true);
			noiseButton.setVisible(true);
			break;
		}
		default:
		{
			slider01Vertical.setVisible(true);
			slider01Horizontal.setVisible(true);
		}
		}
	}
}

void MainComponent::makeAllControlsInvisible()
{
	slider01Vertical.setVisible(false);
	slider01Horizontal.setVisible(false);

	slider02Vertical.setVisible(false);
	slider02Horizontal.setVisible(false);

	rotaryKnob_GearShaped.setVisible(false);

	sawtoothButton.setVisible(false);
	pulseButton.setVisible(false);
	triangleButton.setVisible(false);
	sinewaveButton.setVisible(false);
	noiseButton.setVisible(false);
}
