#===============================================================================
cmake_minimum_required(VERSION 3.15)

project(Phantom VERSION 0.0.1)

#===============================================================================
add_subdirectory(juce)

#===============================================================================
juce_add_plugin(Phantom
        VERSION "0.0.1"
        COMPANY_NAME "Maxwell Audio"
        IS_SYNTH TRUE
        IS_MIDI_EFFECT FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        PLUGIN_MANUFACTURER_CODE Matt
        PLUGIN_CODE Phan
        FORMATS AU VST3
        PRODUCT_NAME "Phantom")

# Generate the JUCE header file for our source code
juce_generate_juce_header(Phantom)

# Declare necessary source files to include into the target
target_sources(Phantom PRIVATE
        src/PhantomEditor.cpp
        src/PhantomProcessor.cpp
        src/PhantomSynth.cpp
        src/PhantomVoice.cpp
        src/PhantomSound.cpp
        src/PhantomOscillator.cpp
        src/PhantomEnvelopeGenerator.cpp
        src/PhantomAmplifier.cpp)

# Preprocessor definitions for our target
target_compile_definitions(Phantom PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

target_link_libraries(Phantom PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp)
