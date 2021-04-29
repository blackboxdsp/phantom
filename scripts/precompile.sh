#!/bin/bash

# CAUTION: This script needs to be run if any resources are added to make sure that
# they are compiled into the build!

start_time=$(date +%s)

PLUGIN_NAME=Phantom
BUILD_TYPE=Debug
FILENAME=${PLUGIN_NAME}Data.h

rm -rf ./bin

cmake -B bin .
cmake --build bin --config "$BUILD_TYPE" --target "${PLUGIN_NAME}_All"

rm -f src/${FILENAME}

cp -f bin/juce_binarydata_${PLUGIN_NAME}Data/JuceLibraryCode/${FILENAME} src/${FILENAME}

convertsecs() {
    ((m = (${1} % 3600) / 60))
    ((s = ${1} % 60))
    printf "%02dm %02ds\n" $m $s
}

end_time=$(date +%s)
execution_time=$(expr $end_time - $start_time)
echo -e "Total time elapsed: $(convertsecs $execution_time)"
