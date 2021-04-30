#!/bin/bash

# Collects the builds and uploads the package to the Google Cloud Storage bucket.

PLUGIN_NAME=Phantom
BUILD_TYPE=Release
DIST_DIR=dist

start_time=$(date +%s)

rm -rf ./bin
rm -rf ./dist

mkdir dist

scripts/build.sh -p -b=${BUILD_TYPE}

if [[ ${OSTYPE} == "darwin"* ]]; then
    if [ ! -d "${DIST_DIR}/macos" ]; then
        mkdir "${DIST_DIR}/macos"
    fi

    cp -r "./bin/${PLUGIN_NAME}_artefacts/VST3/${PLUGIN_NAME}.vst3" "${DIST_DIR}/macos/${PLUGIN_NAME}.vst3"
    cp -r "./bin/${PLUGIN_NAME}_artefacts/AU/${PLUGIN_NAME}.component" "${DIST_DIR}/macos/${PLUGIN_NAME}.component"
else
    if [ ! -d "${DIST_DIR}/windows" ]; then
        mkdir "${DIST_DIR}/windows"
    fi

    cp "./bin/${PLUGIN_NAME}_artefacts/${BUILD_TYPE}/VST3/${PLUGIN_NAME}.vst3/Contents/x86_64-win/${PLUGIN_NAME}.vst3" "${DIST_DIR}/windows/${PLUGIN_NAME}.vst3"
fi
echo -e "\n[Success] Copied plugin binaries!\n"

convertsecs() {
    ((m = (${1} % 3600) / 60))
    ((s = ${1} % 60))
    printf "%02dm %02ds\n" $m $s
}

end_time=$(date +%s)
execution_time=$(expr $end_time - $start_time)
echo -e "Total time elapsed:    $(convertsecs $execution_time)"

me=`basename "$0"`
echo -e "Script name:           ${me}"
