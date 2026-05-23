#pragma once

#include "../SoundEffect.h"
#include <array>

class MagicEffect : public SoundEffect
{
  public:
    void prepare (double newSampleRate, int blockSize) override;
    void trigger() override;
    void renderNextBlock (juce::AudioBuffer<float>& buffer) override;
    bool isActive() const override;

  private:
    struct Oscillator
    {
      double phase = 0.0;
      double frequency = 0.0;
    };

    std::array<Oscillator, 3> oscillators;

    float envelope = 0.0f;
    float attackRate = 0.0f;
    float releaseRate = 0.0f;
    bool attacking = false;
};