/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace PhantomData
{
    extern const char*   montserrat_ttf;
    const int            montserrat_ttfSize = 245708;

    extern const char*   background_png;
    const int            background_pngSize = 114969;

    extern const char*   algorhythm_xml;
    const int            algorhythm_xmlSize = 2561;

    extern const char*   buzzboy_xml;
    const int            buzzboy_xmlSize = 2511;

    extern const char*   noisetap_xml;
    const int            noisetap_xmlSize = 2530;

    extern const char*   overlord_xml;
    const int            overlord_xmlSize = 2495;

    extern const char*   pitcher_xml;
    const int            pitcher_xmlSize = 2460;

    extern const char*   richochet_xml;
    const int            richochet_xmlSize = 2494;

    extern const char*   rumbler_xml;
    const int            rumbler_xmlSize = 2654;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 9;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
