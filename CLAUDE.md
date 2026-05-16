# FX Blaster — CLAUDE.md

## Who is working on this

Complete C++ beginner learning both C++ and JUCE simultaneously through this project.
Explain every non-obvious language concept the first time it appears. Prefer clear,
readable code over clever one-liners. Short inline explanations in responses are good;
long lectures are not.

## What this plugin does

**FX Blaster** is a VST3 + Standalone audio plugin with five sound effect buttons:
Magic, Laser, Explosion, Surprise, Water Wave. Each button triggers a synthesized
effect that plays once and stops on its own.

## JUCE version

8.0.8, fetched automatically via CMake FetchContent (no manual JUCE install needed).

## Build commands

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Standalone exe: `build\AudioPlugin_artefacts\Release\Standalone\FX Blaster.exe`

## Architecture

```
PluginProcessor        owns 5 SoundEffect objects; triggers them; fills the audio buffer
PluginEditor           5 colored TextButtons + Stop button; calls processor methods
SoundEffect            abstract base class (pure virtual: prepare/trigger/render/isActive)
ExplosionEffect        white noise burst with exponential amplitude decay
LaserEffect            sine oscillator with exponentially falling frequency sweep
WaterWaveEffect        one-pole filtered noise with slow LFO on cutoff frequency
MagicEffect            3 detuned sine oscillators mixed through a simple ADSR envelope
SurpriseEffect         ascending C-major arpeggio played as a timed note sequence
```

## Key C++ concepts to explain on first use

- `#pragma once` — include guard; prevents a header being compiled twice
- `virtual` / `override` — lets subclasses replace a base-class method
- Pure virtual (`= 0`) — forces every subclass to implement the method
- `std::unique_ptr` — smart pointer; deletes the object automatically when done
- `std::array` — fixed-size array known at compile time
- `const` on a method — promises the method does not change the object's state
- Lambda (`[&]() { ... }`) — anonymous function; often used for button callbacks

## Key JUCE concepts to explain on first use

- `juce::AudioProcessor` — the base class every plugin processor inherits from
- `processBlock()` — called by the host ~hundreds of times per second; must be fast
  and must NOT allocate heap memory or take locks
- `juce::AudioBuffer<float>` — a 2D array of audio samples (channels × samples)
- `juce::AudioProcessorEditor` — the base class for the plugin's visual window
- `juce::TextButton` — a clickable button widget; set `onClick` to a lambda

## Coding conventions

- C++17, JUCE naming style: `camelCase` for methods/variables, `PascalCase` for classes
- One effect per `.h` / `.cpp` pair inside `Source/`
- No comments unless the WHY is non-obvious
- `processBlock()` must stay real-time safe: no `new`, no `delete`, no mutexes

## Files to know

| File | Role |
| ---- | ---- |
| `CMakeLists.txt` | Build system — lists all sources and JUCE modules |
| `Source/SoundEffect.h` | Abstract base; all effects inherit from this |
| `Source/PluginProcessor.h/.cpp` | Audio engine; owns and drives the 5 effects |
| `Source/PluginEditor.h/.cpp` | GUI window with buttons |
| `Source/*Effect.h/.cpp` | One file-pair per sound effect |
