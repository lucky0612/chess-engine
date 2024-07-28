#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Run CMake
cmake ..

# Build the project
make -j$(nproc)

echo "Build completed successfully!"