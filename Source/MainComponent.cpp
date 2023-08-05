#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
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
    slider01Vertical.setBounds(0, 0, 100, getLocalBounds().getHeight());
    slider01Horizontal.setBounds(120, getLocalBounds().getHeight() - 130, getLocalBounds().getWidth() - 120, 130);
}
