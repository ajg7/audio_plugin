#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p) : AudioProcessorEditor (&p), processor (p)
{
    magicButton.onClick     = [&] { processor.triggerEffect (0); };
    laserButton.onClick     = [&] { processor.triggerEffect (1); };
    explosionButton.onClick = [&] { processor.triggerEffect (2); };
    surpriseButton.onClick  = [&] { processor.triggerEffect (3); };
    waveButton.onClick      = [&] { processor.triggerEffect (4); };
    stopButton.onClick      = [&] { processor.stopAll(); };

    magicButton.setColour     (juce::TextButton::buttonColourId, juce::Colours::mediumpurple);
    laserButton.setColour     (juce::TextButton::buttonColourId, juce::Colours::deepskyblue);
    explosionButton.setColour (juce::TextButton::buttonColourId, juce::Colours::orangered);
    surpriseButton.setColour  (juce::TextButton::buttonColourId, juce::Colours::gold);
    waveButton.setColour      (juce::TextButton::buttonColourId, juce::Colours::teal);
    stopButton.setColour      (juce::TextButton::buttonColourId, juce::Colours::red);

    addAndMakeVisible (magicButton);
    addAndMakeVisible (laserButton);
    addAndMakeVisible (explosionButton);
    addAndMakeVisible (surpriseButton);
    addAndMakeVisible (waveButton);
    addAndMakeVisible (stopButton);

    setSize (300, 420);
}

PluginEditor::~PluginEditor() {}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff1e1e2e));
}

void PluginEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    int  h    = area.getHeight() / 6;

    magicButton    .setBounds (area.removeFromTop (h).reduced (0, 4));
    laserButton    .setBounds (area.removeFromTop (h).reduced (0, 4));
    explosionButton.setBounds (area.removeFromTop (h).reduced (0, 4));
    surpriseButton .setBounds (area.removeFromTop (h).reduced (0, 4));
    waveButton     .setBounds (area.removeFromTop (h).reduced (0, 4));
    stopButton     .setBounds (area.removeFromTop (h).reduced (0, 4));
}
