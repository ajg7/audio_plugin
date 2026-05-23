cmake_minimum_required(VERSION 3.22)

project(audio_plugin VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.8
)

FetchContent_MakeAvailable(JUCE)

juce_add_plugin(AudioPlugin
    COMPANY_NAME "ajg7"
    BUNDLE_ID "com.ajg7.fxblaster"
    PLUGIN_NAME "FX Blaster"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Ajg7
    PLUGIN_CODE FxBl
    FORMATS Standalone VST3
    PRODUCT_NAME "FX Blaster"
)

target_sources(AudioPlugin
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/SoundEffect.h
        Source/Effects/ExplosionEffect.cpp
        Source/Effects/ExplosionEffect.h
        Source/Effects/LaserEffect.cpp
        Source/Effects/LaserEffect.h
        Source/Effects/WaterWaveEffect.cpp
        Source/Effects/WaterWaveEffect.h
        Source/Effects/MagicEffect.cpp
        Source/Effects/MagicEffect.h
        Source/Effects/SurpriseEffect.cpp
        Source/Effects/SurpriseEffect.h
)

target_compile_definitions(AudioPlugin
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(AudioPlugin
    PRIVATE
        juce::juce_audio_utils
        juce::juce_gui_basics
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
