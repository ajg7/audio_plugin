# FX Blaster

A JUCE audio plugin that generates five synthesized sound effects at the click of a button.
Built with C++ and JUCE as a hands-on learning project.

## Effects

| Button     | Sound                    | Technique                       |
| ---------- | ------------------------ | ------------------------------- |
| Magic      | Shimmering sparkle tones | Detuned oscillators + envelope  |
| Laser      | Descending frequency sweep | Chirp oscillator               |
| Explosion  | Percussive noise burst   | Filtered white noise + decay    |
| Surprise   | Ascending arpeggio       | Stepped note sequencer          |
| Water Wave | Rolling ocean texture    | LFO-modulated filtered noise    |

## Prerequisites

- CMake 3.22+
- A C++17 compiler
- Visual Studio 2022 with Desktop development for C++ on Windows
- Git access during the first CMake configure (JUCE is fetched automatically)

## Configure and build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

The Standalone app will be at:

```text
build\AudioPlugin_artefacts\Release\Standalone\FX Blaster.exe
```

The VST3 will be at:

```text
build\AudioPlugin_artefacts\Release\VST3\FX Blaster.vst3
```

## Architecture

```text
PluginProcessor   — audio engine; owns 5 SoundEffect objects, fills the audio buffer
PluginEditor      — UI; 5 colored buttons + Stop button
SoundEffect       — abstract base class all effects inherit from
ExplosionEffect   — noise + exponential amplitude decay
LaserEffect       — sine oscillator with falling frequency sweep
WaterWaveEffect   — bandpass filtered noise with LFO modulation
MagicEffect       — multiple detuned oscillators with ADSR envelope
SurpriseEffect    — ascending arpeggio note sequencer
```

## Learning goals

This project is designed to teach C++ and JUCE from the ground up:

- C++ classes, inheritance, virtual functions, and smart pointers
- Real-time audio processing constraints (`processBlock`)
- JUCE GUI components (`AudioProcessorEditor`, `TextButton`)
- Basic DSP: oscillators, envelopes, filters, and noise
