#!/bin/bash

# Collects the builds and uploads the package to the Google Cloud Storage bucket.

PLUGIN_NAME=Phantom
BUILD_TYPE=Release
DIST_DIR=dist
OPER_SYS=Windows

PACKAGE_STEP=false
DISTRIBUTE_STEP=false

start_time=$(date +%s)

BRANCH="$(git rev-parse --abbrev-ref HEAD)"
if [ "$BRANCH" != "dist" ]; then
    echo -e "[Error] The wrong git branch is checked out. To switch to the correct branch, please use:\n\n\tgit checkout dist"
    
    exit 1;
fi

for i in "$@"; do
    case $i in
    -p|--package)
        PACKAGE_STEP=true
        shift
        ;;
    -d|--distribute)
        DISTRIBUTE_STEP=true
        shift
        ;;
    esac
done

if [ "$PACKAGE_STEP" = true ]; then
    rm -rf ./bin

    scripts/precompile.sh -b=${BUILD_TYPE}

    if [[ ${OSTYPE} == "darwin"* ]]; then
        OPER_SYS=MacOS

        rm -rf "${DIST_DIR}/macos"
        mkdir "${DIST_DIR}/macos" 

        cp -r "./bin/${PLUGIN_NAME}_artefacts/VST3/${PLUGIN_NAME}.vst3" "${DIST_DIR}/macos/${PLUGIN_NAME}.vst3"
        cp -r "./bin/${PLUGIN_NAME}_artefacts/AU/${PLUGIN_NAME}.component" "${DIST_DIR}/macos/${PLUGIN_NAME}.component"

    else
        OPER_SYS=Windows

        rm -rf "${DIST_DIR}/windows" 
        mkdir "${DIST_DIR}/windows"

        cp "./bin/${PLUGIN_NAME}_artefacts/${BUILD_TYPE}/VST3/${PLUGIN_NAME}.vst3/Contents/x86_64-win/${PLUGIN_NAME}.vst3" "${DIST_DIR}/windows/${PLUGIN_NAME}.vst3"
    fi

    git add .
    git commit -m "BUILD: ${OPER_SYS} - $(date)"
    git push

    echo -e "\n[Success] Package plugin for distribution!"
fi

if [ "$DISTRIBUTE_STEP" = true ]; then
    echo -e "\n[TODO] Bash stuff for distributing files."
fi

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
