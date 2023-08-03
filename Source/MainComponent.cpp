#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(slider01);
    slider01.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    //slider01.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);

    g.setColour(juce::Colours::darkorange);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 5.f, 1.f);
}

void MainComponent::resized()
{
    juce::Rectangle localBounds = getLocalBounds();
    int width = localBounds.getWidth();
    int height = localBounds.getHeight();

    slider01.setBounds(10, 10, width / 12, height - 2 * 10);
    //slider01.setBounds(10, 10, 32, 256);
}
