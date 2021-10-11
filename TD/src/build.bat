@ECHO OFF
SetLocal EnableDelayedExpansion


REM Get a list of all the .cpp files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

REM output exe file
SET assembly=main

REM flags, to show warnings etc
SET compilerFlags=-Wall 

REM include headers from other libs and local ones. -I and path
SET includeFlags=-Isrc -I..\dependencies\sfml\include

REM include lib to the linker need to be careful about ordering.
SET linkerFlags=-L..\dependencies\sfml\lib -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lsfml-graphics-s -lsfml-system-s -lsfml-window-s -lopengl32 -lfreetype -lsfml-audio-s -lsfml-system-s -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-network-s -lsfml-system-s -lws2_32 -lsfml-system-s -lwinmm

ECHO "Building %assembly%..."
g++ %cppFilenames% -o %assembly% %compilerFlags% %includeFlags% %linkerFlags%