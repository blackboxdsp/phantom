# Design

This document details both the design and implementation of Phantom's graphical user interface (GUI).

## Layout

The layout of the GUI can be defined in a hierarchical, tree-like structure so that it is easily composable and maintainable. There are key variables, each calculated based off of the dimensions of the plugin's window for the sake of responsiveness, that help to glue the pieces of the GUI together such as a universal knob width, or the height of a margin.

### Hierarchy

- __Plugin window__:
    - pertains to the top-most level in the hierarchy
    - has padding
    - has 4 sections with section spaces between
- __Section__:
    - pertains to horizontal pieces of the plugin
    - has 1 title space (for component titles)
    - has 2+ components
- __Component__:
    - pertains to modular units containing parts of the synthesizer (e.g. oscillator, filter, EG)
    - has padding
    - has 1+ param row(s) with param row spaces between (equal to the padding)
- __Param row__:
    - pertains to horizontal groups of parameters 
    - has 2+ params with param spaces between
- __Param__:
    - pertains to a single controllable parameter on the GUI (e.g. oscillator frequency, filter cutoff)
    - has 1 param title space
    - has 1 param slider with side-padding (could be 0px)

### Variables

- `sectionGap`:
    - pertains to the amount of space (px) between sections
    - is not needed by components*
    - is equal to (1/48) * window height
    - is equal to (3/256) * window width
        - 45px at 4k (3840 x 2160)
- `componentGap`:
    - pertains to the amount of space (px) between components (within a section)
    - is not needed by components* (except the EGs)
    - is equal to the section gap
- `componentPadding`:
    - pertains to the side-padding of components
    - should be in the base component class
- `componentTitleSpaceHeight`:
    - pertains to the height (px) of a component's title (plus more for padding)
    - should be in the base component class
- `paramTitleSpaceHeight`:
    - pertains to the height (px) of a param's title (plus more for padding)
    - should be in the base component class
- `sliderDiameter`:
    - pertains to the diameter (px) of a slider
    - depends on the number of total params in the same param row across all components of the same section
    - is used to allocate areas for components (e.g. the filter is allocated an area the width of three knob widths)
    - is calculated in the editor (not passed to components though)
    - is equal to (1/24) * window width
        - 160px at 4k (3840 x 2160)
- `largeSliderDiameter`:
    - pertains to the diameter (px) of the few larger sliders
    - is equal to (7/128) * window width

\* These variables will have no need in the components therefore they can be removed from any class definitions. 

_NOTE: When dealing with the components inner draw methods, use local bounds to calculate width per slider. It's important that whatever method is chosen is consistent with how the plugin's background image was designed._
