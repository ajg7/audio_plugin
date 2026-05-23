#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Effects/ExplosionEffect.h"
#include "Effects/LaserEffect.h"
#include "Effects/WaterWaveEffect.h"
#include "Effects/MagicEffect.h"
#include "Effects/SurpriseEffect.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor (BusesProperties()
                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    effects[0] = std::make_unique<MagicEffect>();
    effects[1] = std::make_unique<LaserEffect>();
    effects[2] = std::make_unique<ExplosionEffect>();
    effects[3] = std::make_unique<SurpriseEffect>();
    effects[4] = std::make_unique<WaterWaveEffect>();
}

PluginProcessor::~PluginProcessor() {}

const juce::String PluginProcessor::getName() const { return JucePlugin_Name; }

bool PluginProcessor::acceptsMidi() const  { return false; }
bool PluginProcessor::producesMidi() const { return false; }
bool PluginProcessor::isMidiEffect() const { return false; }
double PluginProcessor::getTailLengthSeconds() const { return 0.0; }

int PluginProcessor::getNumPrograms()                                    { return 1; }
int PluginProcessor::getCurrentProgram()                                 { return 0; }
void PluginProcessor::setCurrentProgram (int)                            {}
const juce::String PluginProcessor::getProgramName (int)                 { return {}; }
void PluginProcessor::changeProgramName (int, const juce::String&)       {}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (auto& effect : effects)
        effect->prepare (sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources() {}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    for (auto& effect : effects)
    {
        if (effect->isActive())
            effect->renderNextBlock (buffer);
    }
}

void PluginProcessor::triggerEffect (int index)
{
    stopAll();
    effects[index]->trigger();
}

void PluginProcessor::stopAll()
{
    for (auto& effect : effects)
        effect->stop();
}

bool PluginProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

void PluginProcessor::getStateInformation (juce::MemoryBlock&) {}
void PluginProcessor::setStateInformation (const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
