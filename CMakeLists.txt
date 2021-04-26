# Checks that the installed version of CMake can understand the following commands
cmake_minimum_required(VERSION 3.15)

# Declaring targets and describing source/ binary directories
project(Phantom VERSION 1.0.0)

# Declare dependency on JUCE (as installed on the local system)
add_subdirectory(juce)

juce_add_plugin(Phantom
        VERSION "1.0.0"
        COMPANY_NAME "Black Box DSP"
        IS_SYNTH TRUE
        IS_MIDI_EFFECT FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        PLUGIN_MANUFACTURER_CODE BKBX
        PLUGIN_CODE PHTM
        FORMATS AU VST3
        PRODUCT_NAME "Phantom")

# Generate the JUCE header file for our source code
juce_generate_juce_header(Phantom)

# Declare necessary source files to include into the target
target_sources(Phantom PRIVATE
        src/PhantomAmplifier.cpp
        src/PhantomAnalyzer.cpp
        src/PhantomEditor.cpp
        src/PhantomEnvelopeGenerator.cpp
        src/PhantomFilter.cpp
        src/PhantomLFO.cpp
        src/PhantomMixer.cpp
        src/PhantomOscillator.cpp
        src/PhantomOscilloscope.cpp
        src/PhantomPhasor.cpp
        src/PhantomProcessor.cpp
        src/PhantomSound.cpp
        src/PhantomSynth.cpp
        src/PhantomVoice.cpp
        src/PhantomWaveshaper.cpp)

# Preprocessor definitions for our target
target_compile_definitions(Phantom PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

target_link_libraries(Phantom PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp)
