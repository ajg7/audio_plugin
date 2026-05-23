#pragma once

#include "../SoundEffect.h"

class LaserEffect : public SoundEffect {
  public:
    void prepare (double newSampleRate, int blockSize) override;
    void trigger() override;
    void renderNextBlock (juce::AudioBuffer<float> & buffer) override;
    bool isActive() const override;

    private:
      double phase = 0.0;
      double frequency = 0.0;
};