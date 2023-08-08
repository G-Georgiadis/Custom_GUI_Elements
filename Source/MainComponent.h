#pragma once

#include <JuceHeader.h>
#include "LookAndFeels/Slider_MixingConsoleStyle_LookAndFeel.h"
#include "LookAndFeels/Slider_SynthBipolar_LookAndFeel.h"
#include "Components/WaveformButton.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, juce::ComboBox::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox elementSelectorComboBox;

    Slider_MixingConsoleStyle_LookAndFeel slider_MixingConsoleStyle_LookAndFeel;
    juce::Slider slider01Vertical;
    juce::Slider slider01Horizontal;
    
    Slider_SynthBipolar_LookAndFeel slider_SynthBipolar_LookAndFeel;
    juce::Slider slider02Vertical;
    juce::Slider slider02Horizontal;

    ///** Button background colour */
    //Colour buttonBackgroundColour = Colours::transparentBlack;
    ///** Button state colours */
    //Colour normalButtonColour = Colours::black.brighter(0.1);
    //Colour overbuttonColour = Colours::darkred.darker(0.9);
    //Colour downButonColour = Colours::darkred.darker(0.7);

    //WaveformButton_LookAndFeel waveformButtonLookAndFeel;
    WaveformButton sawtoothButton = WaveformButton(String("sawtoothButton"));
    /*WaveformButton pulseButton = WaveformButton(String("pulseButton"));
    WaveformButton triangleButton = WaveformButton(String("triangleButton"));
    WaveformButton sinewaveButton = WaveformButton(String("sinewaveButton"));
    WaveformButton noiseButton = WaveformButton(String("noiseButton"));*/

    

    void makeAllControlsInvisible();

    // Inherited via Listener
    virtual void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)        
};
