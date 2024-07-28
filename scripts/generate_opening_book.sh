#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Check if PGN file is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_pgn_file>"
    exit 1
fi

PGN_FILE=$1
DB_FILE="data/opening_book.db"

# Navigate to build directory
cd build

# Run the book generator
./book_generator "$PGN_FILE" "$DB_FILE"

echo "Opening book generated successfully!"