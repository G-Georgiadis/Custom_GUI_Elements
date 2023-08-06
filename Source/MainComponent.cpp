#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(elementSelectorComboBox);

    elementSelectorComboBox.addItem(juce::String("Mixing console style slider"), 1001);
    elementSelectorComboBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, slider_MixingConsoleStyle_LookAndFeel.getBackgroundColour());
    elementSelectorComboBox.setColour(juce::ComboBox::ColourIds::outlineColourId, slider_MixingConsoleStyle_LookAndFeel.getOutlineColour());
    //elementSelectorComboBox.setSelectedItemIndex(0, juce::NotificationType::sendNotificationAsync);
    elementSelectorComboBox.addListener(this);

    addChildComponent(slider01Vertical);
    addChildComponent(slider01Horizontal);

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

void MainComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    switch (comboBoxThatHasChanged->getSelectedItemIndex())
    {
    case 0:
    {
        slider01Vertical.setVisible(true);
        slider01Horizontal.setVisible(true);
    }
    }
}
