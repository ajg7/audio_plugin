#pragma once
#include "SoundEffect.h"

class ExplosionEffect : public SoundEffect 
{
  public:
    void prepare (double newSampleRate, int blockSize) override;
    void trigger() override;
    void renderNextBlock (juce::AudioBuffer<float>& buffer) override;
    bool isActive() const override;
  
    private:
      float amplitude = 0.0f;
      bool active = false;

      juce::Random random
};