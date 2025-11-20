# Particle Simulation - Project Silex

A particle physics simulation optimized for Endeavour OS (Arch Linux).

## Description

This is a 2D particle simulation system that models particle movement, collisions, and interactions with barriers. The particles move in 8 directions and can collide with each other and with static barriers. Various simulation scenarios are available with different initial configurations.

**Author:** Kargin Stepan  
**Ported to Linux/SDL2** for Arch-based systems

## Features

- Multiple simulation scenarios (0-8)
- Configurable particle density
- Optional grid lines overlay
- Particle counter display
- Barrier collision detection
- Periodic boundary conditions (infinity mode)
- Optimized for modern CPUs with `-march=native` compilation

## Prerequisites (Arch Linux / Endeavour OS)

Install the required dependencies:

```bash
sudo pacman -S sdl2 sdl2_ttf gcc make cmake
```

## Building

### Method 1: Using Makefile (Recommended)

```bash
make
```

For a debug build:
```bash
make debug
```

### Method 2: Using CMake

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Method 3: Direct compilation

```bash
g++ -std=c++17 -O3 -march=native -o particle_simulation main.cpp -lSDL2 -lSDL2_ttf
```

## Running

```bash
./particle_simulation
```

Or with make:
```bash
make run
```

**Controls:**
- Press `ESC` or close the window to exit

## Configuration

Edit `Parameters.txt` to configure the simulation:

```
procent: 20          # Initial particle density (0-100%)
sleeptime: 5         # Delay between frames in milliseconds
situation: 3         # Simulation scenario (0-8)
lines: 0             # Show grid lines (0=off, 1=on)
masscnt: 0           # Show particle count (0=off, 1=on)
abscollision: 0      # Enable absolute collision detection (0=off, 1=on)
borders: 0           # Enable wall collisions (0=off, 1=on)
infinity: 0          # Enable periodic boundaries (0=off, 1=on)
```

### Simulation Scenarios

- **0**: Random distribution across the entire grid
- **1**: Concentrated rectangular region
- **2-8**: Various pre-configured barrier layouts and particle distributions

## Installation

To install system-wide:

```bash
sudo make install
```

Then run from anywhere:
```bash
particle_simulation
```

To uninstall:
```bash
sudo make uninstall
```

## Optimization

The program is compiled with aggressive optimizations for Arch Linux:
- `-O3`: Maximum optimization level
- `-march=native`: Optimize for your specific CPU architecture
- `-mtune=native`: Tune for your CPU
- `-flto`: Link-time optimization

For best performance, ensure you're running on a system with hardware acceleration enabled for SDL2.

## Performance Tips

1. **Reduce particle density** (`procent`) for smoother simulation
2. **Increase `sleeptime`** if the simulation is too fast
3. **Disable grid lines** (`lines: 0`) for better performance
4. **Smaller window size**: Modify `xsize` and `ysize` in `main.cpp`
5. **Increase cell size**: Modify `cell` value for fewer particles on screen

## Technical Details

- **Graphics Library**: SDL2 with SDL2_ttf for text rendering
- **Language**: C++17
- **Particle System**: Bitfield-based direction encoding (8 directions + barrier flag)
- **Grid Size**: 1850x950 pixels (default)
- **Cell Size**: 4 pixels (default)

## Troubleshooting

### Font not found warning
If you see a font warning, the program will still run but without text display. Install additional fonts:
```bash
sudo pacman -S ttf-dejavu ttf-liberation
```

### SDL2 not found
```bash
sudo pacman -S sdl2 sdl2_ttf
```

### Compilation errors
Make sure you have the development headers:
```bash
sudo pacman -S base-devel
```

## License

Original code by Kargin Stepan. Ported and optimized for Linux.

## Differences from Original

This version has been rewritten from the Windows-only TXLib version:
- Uses SDL2 instead of TXLib for cross-platform compatibility
- Optimized compilation flags for Arch Linux
- Added CMake and Makefile build systems
- Improved code organization and readability
- Better error handling and user feedback
