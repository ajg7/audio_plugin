#include "WaterWaveEffect.h"
#include <cmath>

void WaterWaveEffect::prepare (double newSampleRate, int /* blockSize*/)
{
  sampleRate = newSampleRate;
}

void WaterWaveEffect::trigger()
{
  active = true;

  samplesLeft = (int) (sampleRate * 2.5);
  filterState = 0.0f;
  lowFreqOscillatorPhase = 0.0;
}

bool WaterWaveEffect::isActive() const 
{
  return active;
}

void WaterWaveEffect::renderNextBlock (juce::AudioBuffer<float>& buffer) 
{
  if (!active) return;

  const double twoPi   = 6.28318530717959;
  const double lowFreqOscillatorStep = twoPi * lowFreqOscillatorRate / sampleRate;

  int numChannels = buffer.getNumChannels();
  int numSamples  = buffer.getNumSamples();

  for (int sample = 0; sample < numSamples; ++sample)
    {
        float lowFreqOscillator = (float) std::sin (lowFreqOscillatorPhase);
        float coeff = 0.05f + 0.04f * (lowFreqOscillator * 0.5f + 0.5f);

        float noise = random.nextFloat() * 2.0f - 1.0f;
        filterState = filterState + coeff * (noise - filterState);

        float out = filterState * 0.6f;

        for (int ch = 0; ch < numChannels; ++ch)
            buffer.addSample (ch, sample, out);

        lowFreqOscillatorPhase += lowFreqOscillatorStep;
        if (lowFreqOscillatorPhase > twoPi) lowFreqOscillatorPhase -= twoPi;

        --samplesLeft;
        if (samplesLeft <= 0)
        {
            active = false;
            return;
        }
    }
}