#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Navigate to build directory
cd build

# Run tests
ctest --output-on-failure

echo "All tests passed successfully!"