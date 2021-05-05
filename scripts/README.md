# Scripts

This directory contains bash scripts that each exist to help in the general development of audio plugins. This refers to things like building the source code, copying plugin binaries, pre-compiling resource data, and packaging / distributing the plugin build to a Cloud Storage bucket. Listed below are the scripts found in this directory along with a description on what they do and the flag arguments to execute specific functionality.

## `build.sh`

This script is responsible for building the plugin from the source code, including gathering the resources necessary to do so (i.e. cloning the JUCE repository). It also has other functionality, which one activates by passing flags when running. See more below...

_NOTE: In order to build the plugin, the environment variables, `CMAKE_C_COMPILER` and `CMAKE_CXX_COMPILER`, __MUST__ be set. It's typical for this to be a problem for only Windows users (sigh), in which case I recommend the [MSYS2](https://www.msys2.org/) packages._

### Flag Arguments

- `-c | --copy`
    - Copies the resulting binaries of a fresh plugin build to the appropriate system default directory for plugins (see [INSTALL](../docs/INSTALL.md) to learn where these are)
- `-p | --precompile`
    - Runs `precompile.sh` with the same build type (i.e. "Debug", "Release") 
- `-r | --remove-prev-build`
    - Removes the target builds from both the plugin and JUCE
- `-b=* | --build-type=*`
    - Specifies the build target type (i.e. "Debug", "Release")

## `precompile.sh`

This script is responsible for precompiling files in the `resources/` directory in order to generate a new data header file (for the purpose of overwriting the old one). This is important for when adding a new binary resource (i.e. images, fonts, other resource files) and needs to access it programmatically. 

_NOTE: When adding new resources, one __MUST NOT__ forget to add the file to the `CMakeLists.txt` in the root directory. Without this step, the new resource will not be added into the source code compilation when building the plugin._

### Flag Arguments

- `-b=* | --build-type=*`
    - Specifies the build target type (i.e. "Debug", "Release")

## `release.sh`

This script is responsible for packaging and distributing the plugin builds to the cloud, specifically a Google Cloud Storage bucket. It includes a few extra steps to facilitate that process, particularly enabling it across multiple machines (e.g. one Windows and one MacOS computer).

### Flag Arguments

- `-p | --package`
    - Compiles the plugin and pushes the build onto GitHub (to `dist` branch)
- `-d | --distribute`
    - Pulls builds from GitHub, executes fresh build for matching OS, zips the binaries, and uploads compressed file to Cloud Storage
