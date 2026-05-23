#include "MagicEffect.h"
#include <cmath>

void MagicEffect::prepare (double newSampleRate, int /* blockSize */)
{
  sampleRate = newSampleRate;
  attackRate = 1.0f / (float) (sampleRate * 0.05);
  releaseRate = 1.0f / (float) (sampleRate * 1.5);
}

void MagicEffect::trigger()
{
  oscillators[0].frequency = 1046.5;
  oscillators[1].frequency = 1318.5;
  oscillators[2].frequency = 1568.0;

  for (auto& osc : oscillators) osc.phase = 0.0;

  envelope = 0.0f;
  attacking = true;
  active = true;
}

bool MagicEffect::isActive() const 
{
  return active;
}

void MagicEffect::renderNextBlock (juce::AudioBuffer<float>& buffer) 
{
  if (!active) return;

  const double twoPi = 6.28318530717959;

  int numChannels = buffer.getNumChannels();
  int numSamples  = buffer.getNumSamples();

  for (int sample = 0; sample < numSamples; ++sample)
    {
        float mixed = 0.0f;
        for (auto& osc : oscillators)
        {
            mixed += (float) std::sin (osc.phase);
            osc.phase += twoPi * osc.frequency / sampleRate;
            if (osc.phase > twoPi) osc.phase -= twoPi;
        }
        mixed *= (1.0f / 3.0f);

        if (attacking)
        {
            envelope += attackRate;
            if (envelope >= 1.0f)
            {
                envelope  = 1.0f;
                attacking = false;
            }
        }
        else
        {
            envelope -= releaseRate;
            if (envelope <= 0.0f)
            {
                active = false;
                return;
            }
        }

        float out = mixed * envelope * 0.5f;

        for (int ch = 0; ch < numChannels; ++ch) buffer.addSample (ch, sample, out);
    }
}