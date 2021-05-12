/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace PhantomData
{
    extern const char*   montserrat_ttf;
    const int            montserrat_ttfSize = 245708;

    extern const char*   background_png;
    const int            background_pngSize = 204825;

    extern const char*   algo_xml;
    const int            algo_xmlSize = 1979;

    extern const char*   analog_xml;
    const int            analog_xmlSize = 1982;

    extern const char*   buzzboy_xml;
    const int            buzzboy_xmlSize = 2511;

    extern const char*   noisetap_xml;
    const int            noisetap_xmlSize = 2530;

    extern const char*   overlord_xml;
    const int            overlord_xmlSize = 2495;

    extern const char*   richochet_xml;
    const int            richochet_xmlSize = 2494;

    extern const char*   siren_xml;
    const int            siren_xmlSize = 1981;

    extern const char*   thestack_xml;
    const int            thestack_xmlSize = 1984;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

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
