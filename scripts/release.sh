#!/bin/bash

# Collects the builds and uploads the package to the Google Cloud Storage bucket.

log_exit() {
    echo -e "$1"
    exit 1
}

PLUGIN_NAME=Phantom
BUILD_TYPE=Release
OPER_SYS=Windows

DIST_DIR=dist
DIST_ZIP="phantom.zip"
DIST_BUCKET="mattmaxwell-products"

GCP_CONFIGURATION=mattmaxwell
GCP_PROJECT_ID=mattmaxwell-304801
GCP_SERVICE_ACCOUNT=gcloud-api@mattmaxwell-304801.iam.gserviceaccount.com
GCP_AUTH_KEY_FILE=./conf/gcloud/gcloud-api.json

PACKAGE_STEP=false
DISTRIBUTE_STEP=false

start_time=$(date +%s)

check_for_release() {
    BRANCH="$(git rev-parse --abbrev-ref HEAD)"
    if [ "$BRANCH" != "dist" ];
    then
        echo -e "\t[✘] Branch is set to \"dist\"\n"
        echo -e "If dist branch already exists remotely, please use:\n\n\tgit fetch --all && git checkout dist --\n"
        echo -e "If dist branch does NOT already exist remotely, please the following:\n"
        echo -e "\tgit checkout -b dist ${BRANCH} && git push -u origin dist"

        exit 1
    else
        echo -e "\t[✔] Branch is set to \"dist\""
    fi
}

echo -e "Doing preparation checks...\n"

check_for_release

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

prep_for_packaging() {
    rm -rf ./bin

    git pull
}

copy_plugin_binaries() {
    if [[ ${OSTYPE} == "darwin"* ]]; then
        OPER_SYS=MacOS

        rm -rf "${DIST_DIR}/macos"
        
        mkdir "${DIST_DIR}"
        mkdir "${DIST_DIR}/macos" 

        cp -r "./bin/${PLUGIN_NAME}_artefacts/VST3/${PLUGIN_NAME}.vst3" "${DIST_DIR}/macos/${PLUGIN_NAME}.vst3" || log_exit "\n[Error] Failed to copy plugin binaries (VST3)\n"
        cp -r "./bin/${PLUGIN_NAME}_artefacts/AU/${PLUGIN_NAME}.component" "${DIST_DIR}/macos/${PLUGIN_NAME}.component" || log_exit "\n[Error] Failed to copy plugin binaries (AU)\n"

    else
        OPER_SYS=Windows

        rm -rf "${DIST_DIR}/windows" 

        mkdir "${DIST_DIR}"
        mkdir "${DIST_DIR}/windows"

        cp "./bin/${PLUGIN_NAME}_artefacts/${BUILD_TYPE}/VST3/${PLUGIN_NAME}.vst3/Contents/x86_64-win/${PLUGIN_NAME}.vst3" "${DIST_DIR}/windows/${PLUGIN_NAME}.vst3"  || log_exit "\n[Error] Failed to copy plugin binaries (VST3)\n"
    fi
}

push_plugin_build() {
    git add -f dist
    git commit -m "BUILD: ${OPER_SYS} - $(date)"
    git push
}

package_binaries() {
    prep_for_packaging || log_exit "\n[Error] Failed to prepare for packaging"

    scripts/build.sh -b=${BUILD_TYPE} || log_exit "\n[Error] Failed to build plugin\n"

    copy_plugin_binaries || log_exit "\n[Error] Failed to copy plugin binaries"

    push_plugin_build || log_exit "\n[Error] Failed to push plugin binaries to GitHub"

    echo -e "\n[Success] Packaged plugin for distribution!"
}

if [ "$PACKAGE_STEP" = true ]; then
    package_binaries
fi

check_for_distribution() {
    CURRENT_GCP_PROJECT=$(gcloud config get-value project)
    if [ "$CURRENT_GCP_PROJECT" != "$GCP_PROJECT_ID" ]
    then
        echo -e "\t[✘] Cloud SDK's configuration is set for $GCP_PROJECT_ID\n"
        echo -e "To properly configure the SDK for this project, use:\n\n\tgcloud config configurations activate $GCP_CONFIGURATION"

        exit 1
    else
        echo -e "\t[✔] Cloud SDK's configuration is set for $GCP_PROJECT_ID"
    fi

    CURRENT_GCP_ACCOUNT=$(gcloud config list account --format "value(core.account)")
    if [ "$CURRENT_GCP_ACCOUNT" != "$GCP_SERVICE_ACCOUNT" ]
    then
        echo -e "\t[✘] Cloud IAM service account is set to $GCP_SERVICE_ACCOUNT\n"
        echo -e "To properly set the service account for this project, use:\n\n\tgcloud config set account $GCP_SERVICE_ACCOUNT"
        echo -e "and"
        echo -e "\tgcloud auth activate-service-account $GCP_SERVICE_ACCOUNT --key-file=$GCP_AUTH_KEY_FILE"

        exit 1
    else
        echo -e "\t[✔] Cloud IAM service account is set to $GCP_SERVICE_ACCOUNT\n"
    fi
}

compress_plugin_binaries() {
    if [[ ${OSTYPE} == "darwin"* ]]; then
        zip -r ${DIST_ZIP} dist/ || log_exit "\n[Error] Failed to zip plugin binaries\n"
    else
        7z a -tzip ${DIST_ZIP} dist/ || log_exit "\n[Error] Failed to zip plugin binaries\n"
    fi
    echo -e "\n[Success] Zipped plugin binaries!"
}

upload_plugin_zip() {
    gsutil cp ${DIST_ZIP} gs://staging/${DIST_BUCKET} || log_exit "\n[Error] Failed to copy ${DIST_ZIP} to Cloud Storage\n"
    echo -e "\n[Success] Uploaded plugin zip to Cloud Storage bucket \"${DIST_BUCKET}\"!"
}

cleanup_distribution() {
    rm -f ./${DIST_ZIP}

    git push -d origin dist || log_exit "\n[Error] Failed to delete remote dist branch\n"
    echo -e "\n[Success] Deleted remote branch!"
}

distribute_binaries() {
    check_for_distribution

    package_binaries

    compress_plugin_binaries || log_exit "\n[Error] Failed to compress plugin binaries"

    upload_plugin_zip || log_exit "\n[Error] Failed to upload to Cloud Storage bucket"

    cleanup_distribution || log_exit "\n[Error] Failed to cleanup files from plugin distribution"

    echo -e "\n[Success] Distributed plugin binaries!\n"
}

if [ "$DISTRIBUTE_STEP" = true ]; then
    distribute_binaries
fi

convertsecs() {
    ((m = (${1} % 3600) / 60))
    ((s = ${1} % 60))
    printf "%02dm %02ds\n" $m $s
}

end_time=$(date +%s)
execution_time=$(expr $end_time - $start_time)
echo -e "Total time elapsed:    $(convertsecs $execution_time)"

me=$(basename "$0")
echo -e "Script name:           ${me}"
