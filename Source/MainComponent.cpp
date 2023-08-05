#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(elementSelectorComboBox);

    addAndMakeVisible(slider01Vertical);
    addAndMakeVisible(slider01Horizontal);

    slider01Vertical.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    slider01Horizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

    slider01Vertical.setLookAndFeel(&slider_MixingConsoleStyle_LookAndFeel);
    slider01Horizontal.setLookAndFeel(&slider_MixingConsoleStyle_LookAndFeel);

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    slider01Vertical.setLookAndFeel(nullptr);
    slider01Horizontal.setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    //g.fillAll (juce::Colours::black);
}

void MainComponent::resized()
{
    juce::Rectangle localBounds = getLocalBounds();
    elementSelectorComboBox.setBounds(localBounds.removeFromTop(30));
    localBounds.removeFromTop(10);

    slider01Vertical.setBounds(localBounds.removeFromLeft(100));
    localBounds.removeFromLeft(10);

    slider01Horizontal.setBounds(localBounds.removeFromBottom(140));
}
