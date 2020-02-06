# Phantom

> Modern phase distortion synthesis

<div style="text-align: center">
    <img src="./screenshot.png" alt="Phantom screenshot" title="Phantom running in Ableton Live 10" height="840"/>
</div>

Phantom is a phase distortion synthesizer plugin targeting VST3 and AU for OS X and Windows platforms. [... MORE TEXT ...]. It is compiled using the [JUCE](https://juce.com/) framework for C++.

## Dependencies

- JUCE (v5.4.6)
- VST3 SDK (v3.6.14)

## Usage

Phantom is capable of running with any plugin host as long as it supports VST3 or AU. Please refer to your DAW's manual to see compatible plugin formats.

### Parameters 

- ...

## Contributing

Should you discover any bugs or undesirable behavior, please feel free to open an issue or submit a pull request. I am happy to accept them as long as they don't alter product direction, otherwise I am completely open to discuss any ideas that you may have regarding Phantom.

### Building

Phantom is built using the JUCE framework, which graciously provides project files for various IDEs.

For Windows users, simply navigate to `Builds/VisualStudio2019/Phantom.sln` then build either of the two available configurations. Similarly, OS X users may navigate to `Builds/MACOSX/Phantom.xcodeproj` and build using XCode.

If you have any issues building the plugin, please contact me or file an issue.

## License

Copyright (C) 2020 Matthew Maxwell

This program is free software: you can redistribute it and / or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 

You should have received a copy of the GNU General Public License along with this program. If not, see [http://www.gnu.org/licenses/](http://www.gnu.org/licenses/).
