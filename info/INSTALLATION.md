# Installation

Thank you for checking out Phantom! The process of installing the plugin is incredibly easy - you just need to copy the appropriate binary files (`Phantom.vst3` for Windows and `Phantom.vst3` or `Phantom.component` for MacOS) to the location on your machine where you typically store these files. 

_NOTE: Phantom is still in development, so it is possible that there could be bugs or crashes... however I'd love to know if that happens, so please file an [issue](https://github.com/blackboxdsp/phantom/issues/new), and I'll take a look at it!_

## How To

Most users will not have changed the system's default directory for installing plugins, which is typically:

- __Windows__
    - `C:\Program Files\Common Files\Plugins\VST3\`*
    - `C:\Program Files\Steinberg\Vst3Plugins\`
- __MacOS__
    - `/Library/Audio/Plug-Ins/(VST3 | Components)/`*
    - `~/Library/Audio/Plug-Ins/(VST3 | Components)/`

\* This directory is recommended as its usage is more common among audio software manufacturers.

## Troubleshooting

If you cannot find your problem below, please file an [issue](https://github.com/blackboxdsp/phantom/issues/new) and I'll take a look at it!

- My DAW doesn't recognize the plugin
    - __Windows/MacOS__: Check that your DAW is reading from the path where you copied the plugin binary file(s).
    - __MacOS__: Sometimes the AU validation fails resulting in unrecognition of the plugin, and unfortunately I do not currently have a solution for this problem although I suspect some authentication issues with the plugin metadata (manufacturer code, plugin code, etc.).
- The plugin sounds clicky / there are occasional dropouts
    - __Windows/MacOS__: Yes... unfortunately, the plugin will still have these while it is in development stage, specifically while it hasn't been optimized yet. This is coming soon though!
