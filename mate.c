#define MATE_IMPLEMENTATION // Adds function implementations 
#include "include/mate.h"

i32 main() {
  StartBuild();
  {
    Executable executable = CreateExecutable((ExecutableOptions){
        .output = "main",   // output name, in windows this becomes `main.exe` automatically
        .flags = "-Wall -g" // adds warnings and debug symbols
    });

    // Files to compile
    AddFile(executable, "./src/*.c");
    AddIncludePaths(executable, "C:/msys64/mingw64/include");
    AddLibraryPaths(executable, "C:/msys64/mingw64/lib");

    // Compiles all files parallely with samurai
    InstallExecutable(executable);

    // Runs `./build/main` or `./build/main.exe` depending on the platform
    RunCommand(executable.outputPath);
  }
  EndBuild();
}