#include "LaserEffect.h"
#include <cmath>

void LaserEffect::prepare (double newSampleRate, int /*blockSize */) 
{
  sampleRate = newSampleRate;
}

void LaserEffect::trigger() 
{
  phase = 0.0;
  frequency = 2000.0;
  active = true;
}

bool LaserEffect::isActive() const
{
  return active;
}

void LaserEffect::renderNextBlock (juce::AudioBuffer<float>& buffer) 
{
  if (!active) return;
  const double sweepRate = 0.9995;
  const double stopFreq = 80.0;
  const double twoPi = 6.28318530717959;

  int numChannels = buffer.getNumChannels();
  int numSamples = buffer.getNumSamples();

  for (int sample = 0; sample < numSamples; ++sample) 
  {
    float out = (float) std::sin (phase) * 0.7f;
    for (int ch = 0; ch < numChannels; ++ch) buffer.addSample (ch, sample, out);

    phase += twoPi * frequency / sampleRate;

    if (phase > twoPi) phase -= twoPi;

    frequency *= sweepRate;

    if (frequency < stopFreq)
    {
      active = false;
      return;
    }
  }
}