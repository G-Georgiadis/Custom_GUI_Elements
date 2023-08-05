#pragma once

#include <JuceHeader.h>
#include "LookAndFeels/Slider_MixingConsoleStyle_LookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
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

    juce::Slider slider01Vertical;
    juce::Slider slider01Horizontal;
    Slider_MixingConsoleStyle_LookAndFeel slider_MixingConsoleStyle_LookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
