#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
    addAndMakeVisible(elementSelectorComboBox);

    elementSelectorComboBox.addItem(juce::String("Mixing console style slider"), 1001);
    elementSelectorComboBox.addItem(juce::String("Synth bipolar slider"), 1002);

    elementSelectorComboBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, slider_MixingConsoleStyle_LookAndFeel.getBackgroundColour());
    elementSelectorComboBox.setColour(juce::ComboBox::ColourIds::outlineColourId, slider_MixingConsoleStyle_LookAndFeel.getOutlineColour());

    elementSelectorComboBox.setSelectedItemIndex(1);
    
    elementSelectorComboBox.addListener(this);

    /** Mixing console style faders */
    addChildComponent(slider01Vertical);
    addChildComponent(slider01Horizontal);
    /** Synth bipolar sliders */
    addChildComponent(slider02Vertical);
    addChildComponent(slider02Horizontal);

    slider01Vertical.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    slider01Horizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

    slider02Vertical.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
    slider02Horizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

    slider01Vertical.setLookAndFeel(&slider_MixingConsoleStyle_LookAndFeel);
    slider01Horizontal.setLookAndFeel(&slider_MixingConsoleStyle_LookAndFeel);

    slider02Vertical.setLookAndFeel(&slider_SynthBipolar_LookAndFeel);
    slider02Horizontal.setLookAndFeel(&slider_SynthBipolar_LookAndFeel);

    
    slider02Vertical.setRange(-1, 1, 0.01);
    slider02Horizontal.setRange(-1, 1, 0.01);

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
    
}

void MainComponent::resized()
{
    juce::Rectangle localBounds = getLocalBounds();
    elementSelectorComboBox.setBounds(localBounds.removeFromTop(30));
    localBounds.removeFromTop(10);
    
    auto verticalSliderBounds = localBounds.removeFromLeft(100);
    localBounds.removeFromLeft(10);
    auto horizontalSliderBounds = localBounds.removeFromBottom(140);

    slider01Vertical.setBounds(verticalSliderBounds);
    slider01Horizontal.setBounds(horizontalSliderBounds);


    slider02Vertical.setBounds(verticalSliderBounds);
    slider02Horizontal.setBounds(horizontalSliderBounds);
}

void MainComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &elementSelectorComboBox)
    {
        makeAllControlsInvisible();

        switch (comboBoxThatHasChanged->getSelectedItemIndex())
        {
        case 0:
        {
            slider01Vertical.setVisible(true);
            slider01Horizontal.setVisible(true);
            break;

        }
        case 1:
        {
            slider02Vertical.setVisible(true);
            slider02Horizontal.setVisible(true);
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
}
