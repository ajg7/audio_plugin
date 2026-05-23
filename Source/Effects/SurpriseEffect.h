#pragma once

#include "../SoundEffect.h"
#include <array>

class SurpriseEffect : public SoundEffect
{
public:
    void prepare (double newSampleRate, int blockSize) override;
    void trigger() override;
    void renderNextBlock (juce::AudioBuffer<float>& buffer) override;
    bool isActive() const override;

private:
    std::array<double, 4> noteFrequencies = { 523.25, 659.25, 783.99, 1046.5 };

    int    noteIndex      = 0;
    int    samplesLeft    = 0;
    int    gapSamples     = 0;
    bool   inGap          = false;

    double phase          = 0.0;
    float  envelope       = 0.0f;
    float  releaseRate    = 0.0f;
};
