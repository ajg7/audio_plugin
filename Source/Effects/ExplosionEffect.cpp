#include "ExplosionEffect.h"

void ExplosionEffect::prepare (double newSampleRate, int /*blockSize*/)
{
    sampleRate = newSampleRate;
}

void ExplosionEffect::trigger()
{
    amplitude = 1.0f; // Start with full amplitude
    active = true;
}

bool ExplosionEffect::isActive() const
{
  return active;
}

void ExplosionEffect::renderNextBlock (juce::AudioBuffer<float>& buffer)
{
  if (!active) return;
  const float decayRate = 0.9998f;
  const float threshold = 0.001f;

  int numChannels = buffer.getNumChannels();
  int numSamples = buffer.getNumSamples();

  for (int sample = 0; sample < numSamples; ++sample) 
  {
    float noise = random.nextFloat() * 2.0f - 1.0f;
    float out = noise * amplitude;

    for (int ch = 0; ch < numChannels; ++ch) buffer.addSample (ch, sample, out);
    amplitude *= decayRate;
    if (amplitude < threshold) 
    {
      active = false;
      break;
    }
  }
}