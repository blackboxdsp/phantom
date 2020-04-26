@echo off
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=2& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/doc/artwork/VST_Logo_Steinberg.ico C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/PlugIn.ico || (set FAIL_LINE=3& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/cmake/modules/../templates/desktop.ini.in C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/desktop.ini || (set FAIL_LINE=4& goto :ABORT)
attrib +s C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/desktop.ini || (set FAIL_LINE=5& goto :ABORT)
attrib +s C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/PlugIn.ico || (set FAIL_LINE=6& goto :ABORT)
attrib +s C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3 || (set FAIL_LINE=7& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\bin || (set FAIL_LINE=8& goto :ABORT)
C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\bin\validator.exe C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/x86_64-win/againsimple.vst3 || (set FAIL_LINE=9& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=10& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/again.uidesc C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=11& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=12& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/background.png C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=13& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=14& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/slider_background.png C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=15& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=16& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/slider_handle.png C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=17& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=18& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/slider_handle_2.0x.png C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=19& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=20& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/vu_on.png C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=21& goto :ABORT)
cd /D C:\dev\projects\audio\phantom\phantom\vst3-sdk\out\build\x64-Debug\public.sdk\samples\vst\again || (set FAIL_LINE=22& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy C:/dev/projects/audio/phantom/phantom/vst3-sdk/public.sdk/samples/vst/again/resource/vu_off.png C:/dev/projects/audio/phantom/phantom/vst3-sdk/out/build/x64-Debug/VST3/Debug/againsimple.vst3/Contents/Resources || (set FAIL_LINE=23& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%