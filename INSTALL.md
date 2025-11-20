# Installation Guide for Endeavour OS / Arch Linux

## Quick Start

1. **Install dependencies:**
   ```bash
   sudo pacman -S sdl2 sdl2_ttf gcc make
   ```

2. **Build the project:**
   ```bash
   ./build.sh
   ```
   
   Or manually:
   ```bash
   make
   ```

3. **Run the simulation:**
   ```bash
   ./particle_simulation
   ```

## Detailed Installation

### Step 1: Install Dependencies

The project requires SDL2 libraries and a C++ compiler. On Arch Linux / Endeavour OS:

```bash
sudo pacman -S sdl2 sdl2_ttf gcc make base-devel
```

Optional (for fonts):
```bash
sudo pacman -S ttf-dejavu ttf-liberation
```

### Step 2: Clone or Download the Repository

If you cloned from git:
```bash
cd Project_Silex
```

### Step 3: Build the Application

Option A - Using the build script (recommended):
```bash
chmod +x build.sh
./build.sh
```

Option B - Using Make directly:
```bash
make
```

Option C - Using CMake:
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
```

### Step 4: Run the Simulation

```bash
./particle_simulation
```

## Configuration

Before running, you can edit `Parameters.txt` to customize the simulation:

```bash
nano Parameters.txt
```

Available parameters:
- `procent`: Particle density (0-100%)
- `sleeptime`: Frame delay in milliseconds
- `situation`: Scenario number (0-8)
- `lines`: Show grid (0 or 1)
- `masscnt`: Show particle count (0 or 1)
- `abscollision`: Collision detection (0 or 1)
- `borders`: Wall collisions (0 or 1)
- `infinity`: Periodic boundaries (0 or 1)

## System-Wide Installation (Optional)

To install the application system-wide:

```bash
sudo make install
```

This will:
- Install the binary to `/usr/local/bin/particle_simulation`
- Install configuration to `/usr/local/share/particle_simulation/`

After installation, you can run from anywhere:
```bash
particle_simulation
```

To uninstall:
```bash
sudo make uninstall
```

## Troubleshooting

### SDL2 Headers Not Found

If compilation fails with "SDL2/SDL.h: No such file or directory":
```bash
sudo pacman -S sdl2 sdl2_ttf
```

### Missing pkg-config

```bash
sudo pacman -S pkg-config
```

### Font Warnings at Runtime

The program will run without fonts but won't display text. Install fonts:
```bash
sudo pacman -S ttf-dejavu ttf-liberation
```

### Performance Issues

1. Lower the particle density in `Parameters.txt`
2. Increase `sleeptime` value
3. Disable grid lines (`lines: 0`)
4. Build with debug flags to check for issues:
   ```bash
   make debug
   ```

### AUR Helper Installation

If you prefer using an AUR helper like `yay` or `paru`, the dependencies can also be installed:
```bash
yay -S sdl2 sdl2_ttf
```

## Development

To rebuild after making changes:
```bash
make clean
make
```

For debugging:
```bash
make debug
./particle_simulation
```

## Hardware Acceleration

For best performance, ensure SDL2 can use hardware acceleration:

```bash
# Check if hardware acceleration is available
glxinfo | grep "direct rendering"
```

Should output "direct rendering: Yes"

If not, you may need to install graphics drivers:
- For AMD: `sudo pacman -S mesa vulkan-radeon`
- For Intel: `sudo pacman -S mesa vulkan-intel`
- For NVIDIA: `sudo pacman -S nvidia nvidia-utils`

## Additional Resources

- SDL2 Documentation: https://wiki.libsdl.org/
- Arch Wiki SDL: https://wiki.archlinux.org/title/SDL
- Endeavour OS Forum: https://forum.endeavouros.com/
