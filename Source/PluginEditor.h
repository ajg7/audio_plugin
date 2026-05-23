#pragma once
#include "PluginProcessor.h"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    PluginProcessor& processor;

    juce::TextButton magicButton     { "Magic" };
    juce::TextButton laserButton     { "Laser" };
    juce::TextButton explosionButton { "Explosion" };
    juce::TextButton surpriseButton  { "Surprise" };
    juce::TextButton waveButton      { "Water Wave" };
    juce::TextButton stopButton      { "Stop" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
