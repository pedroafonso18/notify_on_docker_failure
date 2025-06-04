#!/bin/bash

# Clean build directory if it exists
if [ -d "build" ]; then
    echo "Cleaning build directory..."
    rm -rf build
fi

# Create fresh build directory
mkdir -p build
cd build

# Configure with CMake
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build .

# Return to original directory
cd ..

echo "Build completed! Check build/bin/notifica-rabbit" 