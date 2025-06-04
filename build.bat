@echo off
if not exist build mkdir build
cd build
cmake ..
cmake --build . --config Release
cd ..
echo Build completed! Check build/bin/Release/notifica-rabbit.exe 