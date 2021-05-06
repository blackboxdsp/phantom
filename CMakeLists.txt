# Checks that the installed version of CMake can understand the following commands
cmake_minimum_required(VERSION 3.15)

# Declaring targets and describing source/ binary directories
project(Phantom VERSION 1.0.0)

# Declare dependency on JUCE (as installed on the local system)
add_subdirectory(juce)

# Define plugin metadata
juce_add_plugin(Phantom
        VERSION "1.0.0"
        COMPANY_NAME "Black Box DSP"
        COMPANY_WEBSITE "https://blackboxdsp.com"
        PRODUCT_NAME Phantom
        PLUGIN_NAME Phantom
        PLUGIN_MANUFACTURER_CODE Bkbx
        PLUGIN_CODE Phtm
        BUNDLE_ID "com.blackboxdsp.phantom"
        FORMATS VST3 AU AUv3
        VST3_CATEGORIES Instrument Synth
        AU_MAIN_TYPE kAudioUnitType_MusicDevice
        IS_SYNTH TRUE
        IS_MIDI_EFFECT FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE)

# Generate the JUCE header file for our source code
juce_generate_juce_header(Phantom)

# Declare necessary source files to include into the target
target_sources(Phantom PRIVATE
        src/components/PhantomAnalyzer.cpp
        src/components/PhantomOscilloscope.cpp
        src/editor/PhantomEditor.cpp
        src/effects/PhantomAmplifier.cpp
        src/effects/PhantomFilter.cpp
        src/effects/PhantomMixer.cpp
        src/effects/PhantomPhasor.cpp
        src/effects/PhantomWaveshaper.cpp
        src/generators/PhantomEnvelope.cpp
        src/generators/PhantomLFO.cpp
        src/generators/PhantomOscillator.cpp
        src/processor/PhantomProcessor.cpp
        src/processor/PhantomSound.cpp
        src/processor/PhantomSynth.cpp
        src/processor/PhantomVoice.cpp)

# Preprocessor definitions for our target
target_compile_definitions(Phantom PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

# Add binary data from resources folder
juce_add_binary_data(PhantomData HEADER_NAME PhantomData.h NAMESPACE PhantomData SOURCES
        resources/fonts/montserrat.ttf
        resources/presets/algo.xml
        resources/presets/analog.xml
        resources/presets/buzz-boy.xml
        resources/presets/noise-tap.xml
        resources/presets/overlord.xml
        resources/presets/richochet.xml
        resources/presets/siren.xml
        resources/presets/the-stack.xml)

# Link libraries to the plugin's source code and other resources (i.e. binary data)
target_link_libraries(Phantom PRIVATE
        PhantomData
        juce::juce_audio_utils
        juce::juce_dsp)
