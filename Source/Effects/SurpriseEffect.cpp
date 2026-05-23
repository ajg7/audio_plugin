#include "SurpriseEffect.h"
#include <cmath>

void SurpriseEffect::prepare (double newSampleRate, int /*blockSize*/)
{
    sampleRate  = newSampleRate;
    releaseRate = 1.0f / (float) (sampleRate * 0.015);
    gapSamples  = (int) (sampleRate * 0.03);
}

void SurpriseEffect::trigger()
{
    noteIndex   = 0;
    phase       = 0.0;
    envelope    = 1.0f;
    inGap       = false;
    active      = true;
    samplesLeft = (int) (sampleRate * 0.12);
}

bool SurpriseEffect::isActive() const
{
    return active;
}

void SurpriseEffect::renderNextBlock (juce::AudioBuffer<float>& buffer)
{
    if (!active) return;

    const double twoPi = 6.28318530717959;

    int numChannels = buffer.getNumChannels();
    int numSamples  = buffer.getNumSamples();

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float out = 0.0f;

        if (inGap)
        {
            --samplesLeft;
            if (samplesLeft <= 0)
            {
                ++noteIndex;
                if (noteIndex >= (int) noteFrequencies.size())
                {
                    active = false;
                    return;
                }
                phase       = 0.0;
                envelope    = 1.0f;
                inGap       = false;
                samplesLeft = (int) (sampleRate * 0.12);
            }
        }
        else
        {
            envelope -= releaseRate;
            if (envelope <= 0.0f)
            {
                envelope    = 0.0f;
                inGap       = true;
                samplesLeft = gapSamples;
            }

            out    = (float) std::sin (phase) * envelope * 0.5f;
            phase += twoPi * noteFrequencies[noteIndex] / sampleRate;
            if (phase > twoPi)
                phase -= twoPi;
        }

        for (int ch = 0; ch < numChannels; ++ch)
            buffer.addSample (ch, sample, out);
    }
}
