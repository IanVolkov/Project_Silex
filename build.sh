#!/bin/bash
# Build script for Particle Simulation on Arch Linux / Endeavour OS

set -e

echo "=== Particle Simulation Build Script ==="
echo ""

# Check if running on Arch-based system
if ! command -v pacman &> /dev/null; then
    echo "Warning: This script is designed for Arch Linux / Endeavour OS"
    echo "You may need to adapt it for your distribution."
    echo ""
fi

# Check for dependencies
echo "Checking dependencies..."
MISSING_DEPS=()

if ! pkg-config --exists sdl2; then
    MISSING_DEPS+=("sdl2")
fi

if ! pkg-config --exists SDL2_ttf; then
    MISSING_DEPS+=("sdl2_ttf")
fi

if ! command -v g++ &> /dev/null; then
    MISSING_DEPS+=("gcc")
fi

if [ ${#MISSING_DEPS[@]} -gt 0 ]; then
    echo "Missing dependencies: ${MISSING_DEPS[*]}"
    echo ""
    echo "On Arch Linux / Endeavour OS, install with:"
    echo "  sudo pacman -S sdl2 sdl2_ttf gcc make"
    echo ""
    exit 1
fi

echo "All dependencies found!"
echo ""

# Build the project
echo "Building particle_simulation..."
make clean 2>/dev/null || true
make

if [ $? -eq 0 ]; then
    echo ""
    echo "=== Build successful! ==="
    echo ""
    echo "Run the simulation with:"
    echo "  ./particle_simulation"
    echo ""
    echo "Or install system-wide with:"
    echo "  sudo make install"
    echo ""
else
    echo ""
    echo "Build failed. Please check the error messages above."
    exit 1
fi
