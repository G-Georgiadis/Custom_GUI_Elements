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
    /** The combo box for GUI element selection */
    juce::ComboBox elementSelectorComboBox;

    /** LookAndFeel for the mixing console style slider */
    Slider_MixingConsoleStyle_LookAndFeel slider_MixingConsoleStyle_LookAndFeel;
    /** Vertical mixing console style slider */
    juce::Slider slider01Vertical;
    /** Horizontal mixing console style slider */
    juce::Slider slider01Horizontal;
    
    /** LookAndFeel for the synth bipolar slider */
    Slider_SynthBipolar_LookAndFeel slider_SynthBipolar_LookAndFeel;
    /** Vertical bipolar slider */
    juce::Slider slider02Vertical;
    /** Horizontal bipolar slider */
    juce::Slider slider02Horizontal;


    // Waveform selection buttons
    
    WaveformButton sawtoothButton = WaveformButton(String("sawtoothButton"));
    WaveformButton pulseButton = WaveformButton(String("pulseButton"));
    WaveformButton triangleButton = WaveformButton(String("triangleButton"));
    WaveformButton sinewaveButton = WaveformButton(String("sinewaveButton"));
    WaveformButton noiseButton = WaveformButton(String("noiseButton"));

    
    void makeAllControlsInvisible();

    // Inherited via Listener
    virtual void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)        
};
