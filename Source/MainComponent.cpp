#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(slider01);

    slider01.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

    slider01.setLookAndFeel(&levelSlider01LookAndFeel);

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    slider01.setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    //g.fillAll (juce::Colours::black);
}

void MainComponent::resized()
{
    slider01.setBounds(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight());
}
