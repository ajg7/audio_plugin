#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class SoundEffect 
{
  public:
    virtual ~SoundEffect() = default;

    virtual void prepare (double sampleRate, int blockSize) = 0;

    virtual void trigger() = 0;

    virtual void renderNextBlock (juce::AudioBuffer<float>& buffer) = 0;

    virtual bool isActive() const = 0;

  protected:
    double sampleRate = 44100.0;
};