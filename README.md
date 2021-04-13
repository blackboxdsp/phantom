# Phantom (v.1.0.0-alpha)

[![phantom](https://github.com/maxwellmattryan/phantom/workflows/phantom/badge.svg)](https://github.com/maxwellmattryan/phantom/actions?query=workflow%3Aphantom)
[![JUCE](https://img.shields.io/badge/JUCE-v6.0.7-ff69b4)](https://juce.com/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

> Modern phase distortion synthesis

<div style="text-align: center">
    <img 
        src="https://storage.googleapis.com/mattmaxwell-assets/portfolio/projects/phantom.png" 
        alt="Phantom screenshot" 
        title="Phantom running in Ableton Live 10"
        width="720"
    />
</div>

Phantom is a phase distortion synthesizer plugin targeting VST3 and AU for OS X and Windows platforms. It uses the unique method of *phase distortion synthesis* to create sound and is capable of some truly bizarre sound design, which is really what makes it fun to use.

## Dependencies

- JUCE (v6.0.7)
- VST3 SDK (v3.6.14)

## Usage

Phantom is capable of running with any plugin host as long as it supports VST3 or AU. Please refer to your DAW's manual to see compatible plugin formats.

## Contributing

Should you discover any bugs or undesirable behavior, please feel free to open an issue or submit a pull request. I am happy to accept them as long as they don't alter product direction, otherwise I am completely open to discuss any ideas that you may have regarding Phantom.

### Building

Phantom is built using the JUCE framework, which graciously provides project files for various IDEs. To compile the source code into usable plugin binaries, please download [CMake](https://cmake.org/) and run the `build.sh` script located at the root-directory of the repository.

If you have any issues building the plugin, please contact me or file an issue.

## License

Copyright (C) 2020 Matthew Maxwell

This program is free software: you can redistribute it and / or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 

You should have received a copy of the GNU General Public License along with this program. If not, see [http://www.gnu.org/licenses/](http://www.gnu.org/licenses/).
