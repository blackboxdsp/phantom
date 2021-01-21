#!/bin/bash

start_time=$(date +%s)

BUILD_TYPE=Debug
COPY_BUILD_STEP=false
DAW_TO_OPEN=""
REMOVE_PREV_BUILD=false

for i in "$@"; do
    case $i in
    -c|--copy)
        COPY_BUILD_STEP=true
        shift
        ;;
    -d=*|--daw=*)
        DAW_TO_OPEN="${i#*=}"
        shift
        ;;
    -r|--remove-prev-build)
        REMOVE_PREV_BUILD=true
        shift
        ;;
    -t=*|--type=*)
        BUILD_TYPE="${i#*=}"
        shift
        ;;
    esac
done

if [ "$REMOVE_PREV_BUILD" = true ]; then
    rm -rf ./build
    rm -rf ./juce/build
    echo -e "SUCCESS: Removed previous build's folders and cache\n"
fi

if [ ! -d "./juce" ]; then
    git clone https://github.com/juce-framework/JUCE.git
    mv JUCE/ juce/
    echo -e "\nSUCCESS: Cloned JUCE repository\n"
fi

if [ ! -d "./juce/build" ]; then
    cd ./juce

    echo -e "Configuring (JUCE)...\n"
    cmake -B build .
    echo -e "\nSUCCESS: Configured JUCE build\n"

    echo -e "Building (JUCE)...\n"
    cmake --build build
    echo -e "\nSUCCESS: Built JUCE libraries and targets\n"

    cd ../
fi

echo -e "Configuring (Phantom)...\n"
cmake -B phantom/build
echo -e "\nSUCCESS: Configured plugin build\n"

echo -e "Building (Phantom)...\n"
cmake --build phantom/build --config "$BUILD_TYPE" --target Phantom_All
echo -e "\nSUCCESS: Built plugin executable(s)\n"

if [ ! -z "$DAW_TO_OPEN" ]; then
    start "$DAW_TO_OPEN"
    echo -e "SUCCESS: Launched ${DAW_TO_OPEN} application\n"
fi

if [ "$COPY_BUILD_STEP" = true ]; then
    if [[ "$OSTYPE" == "darwin"* ]]; then
        rm -rf /Library/Audio/Plug-Ins/VST3/Phantom.vst3
        cp -r ./phantom/build/Phantom/Phantom_artefacts/${BUILD_TYPE}/VST3/Phantom.vst3 /Library/Audio/Plug-Ins/VST3/Phantom.vst3
        echo -e "SUCCESS: Copied VST3 bundle to plugins directory\n"

        rm -rf /Library/Audio/Plug-Ins/Components/Phantom.component
        cp -r ./phantom/build/Phantom/Phantom_artefacts/${BUILD_TYPE}/AU/Phantom.component /Library/Audio/Plug-Ins/Components/Phantom.component
        echo -e "SUCCESS: Copied AU bundle to plugins directory\n"
    else
        rm -f /c/Program\ Files/Common\ Files/VST3/Phantom.vst3
        cp ./phantom/build/Phantom/Phantom_artefacts/${BUILD_TYPE}/VST3/Phantom.vst3/Contents/x86_64-win/Phantom.vst3 /c/Program\ Files/Common\ Files/VST3/Phantom.vst3
        echo -e "SUCCESS: Copied VST3 bundle to plugins directory\n"
    fi
fi

convertsecs() {
    ((m = (${1} % 3600) / 60))
    ((s = ${1} % 60))
    printf "%02dm %02ds\n" $m $s
}

end_time=$(date +%s)
execution_time=$(expr $end_time - $start_time)
echo -e "Total time elapsed: $(convertsecs $execution_time)"