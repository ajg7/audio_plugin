#pragma once
#include "../SoundEffect.h"

class WaterWaveEffect : public SoundEffect 
{
  public:
    void prepare (double newSampleRate, int blockSize) override;
    void trigger() override;
    void renderNextBlock (juce::AudioBuffer<float>& buffer) override;
    bool isActive() const override;

  private:
    int samplesLeft = 0;
    float filterState = 0.0f;
    double lowFreqOscillatorPhase = 0.0;
    double lowFreqOscillatorRate  = 0.3;

    juce::Random random;
};