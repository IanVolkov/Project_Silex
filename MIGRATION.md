# Migration Guide: Windows to Endeavour OS (Arch Linux)

This guide helps you transition from the Windows version of Project Silex to the new Linux version.

## What Changed

### Graphics Library
- **Windows**: TXLib.h (Windows GDI-based)
- **Linux**: SDL2 (cross-platform, hardware-accelerated)

### Build System
- **Windows**: Visual Studio solution files (.sln, .vcxproj)
- **Linux**: Makefile and CMake

### Platform
- **Windows**: Windows 7/8/10/11
- **Linux**: Endeavour OS, Arch Linux, and other Linux distributions

## Side-by-Side Comparison

| Feature | Windows Version | Linux Version |
|---------|----------------|---------------|
| Graphics | TXLib.h | SDL2 |
| Compiler | MSVC (Visual Studio) | GCC/Clang |
| Build | Visual Studio | Make/CMake |
| Font Rendering | TXLib built-in | SDL2_ttf |
| Input Handling | `_kbhit()` | SDL Event System |
| Sleep Function | `Sleep()` (ms) | `SDL_Delay()` (ms) |
| Window Creation | `txCreateWindow()` | SDL2 Window/Renderer |

## Configuration Compatibility

The `Parameters.txt` file format is **100% compatible** between versions. You can use the same configuration file on both platforms.

```
procent: 20
sleeptime: 5
situation: 3
lines: 0
masscnt: 0
abscollision: 0
borders: 0
infinity: 0
```

## Visual Differences

### Rendering Quality
- **Windows version**: Software rendering via GDI
- **Linux version**: Hardware-accelerated rendering via SDL2
- **Result**: Smoother animation and better performance on Linux

### Font Display
- **Windows**: Uses system fonts automatically
- **Linux**: Uses DejaVu Sans or Liberation fonts
- **Note**: Text may look slightly different due to different font rendering

### Colors
The color scheme is preserved:
- White particles: Regular particles
- Red particles: Barrier/wall particles
- Gray lines: Grid overlay (when enabled)
- Yellow text: Particle counter (when enabled)

## File Compatibility

### Keep These Files
- ✅ `Parameters.txt` - Works on both platforms
- ✅ Custom scenario configurations

### No Longer Needed (Linux)
- ❌ `Final project.sln` - Visual Studio solution
- ❌ `Final project.vcxproj*` - Visual Studio project files
- ❌ `TXLib.h` - Windows-only library
- ❌ `x64/` directory - Windows build output
- ❌ `Final project.cpp` - Replaced by `main.cpp`

### New Files (Linux)
- ✅ `main.cpp` - Rewritten source code
- ✅ `Makefile` - Build configuration
- ✅ `CMakeLists.txt` - Alternative build system
- ✅ `build.sh` - Build automation script
- ✅ `README.md` - Documentation
- ✅ `INSTALL.md` - Installation guide
- ✅ `.gitignore` - Git ignore rules

## Setting Up on Endeavour OS

### 1. Install System
If you're new to Endeavour OS:
1. Download from https://endeavouros.com/
2. Create bootable USB
3. Install alongside or replace Windows
4. Choose a desktop environment (KDE, XFCE, GNOME, etc.)

### 2. Install Dependencies
```bash
sudo pacman -S sdl2 sdl2_ttf gcc make base-devel
```

### 3. Build the Project
```bash
./build.sh
```

Or manually:
```bash
make
```

### 4. Run
```bash
./particle_simulation
```

## Performance Comparison

### Windows Version
- Software rendering (CPU-based)
- Limited optimization
- Frame rate: ~30-60 FPS with default settings

### Linux Version
- Hardware-accelerated rendering (GPU)
- Compiler optimizations (-O3, -march=native)
- Frame rate: 60+ FPS with default settings
- Better CPU efficiency

## Common Migration Issues

### Issue: "Cannot find SDL2"
**Solution**: Install dependencies
```bash
sudo pacman -S sdl2 sdl2_ttf
```

### Issue: "Font not found" warning
**Solution**: Install fonts
```bash
sudo pacman -S ttf-dejavu ttf-liberation
```

### Issue: Particles look different
**Explanation**: The circle rendering algorithm is optimized differently. The visual appearance should be nearly identical but may have minor differences due to SDL2's rendering.

### Issue: Different performance characteristics
**Explanation**: Hardware acceleration means performance varies with GPU. The Linux version is generally faster on modern hardware.

### Issue: Window doesn't open
**Check**: Graphics drivers are installed
```bash
# For AMD
sudo pacman -S mesa vulkan-radeon

# For Intel
sudo pacman -S mesa vulkan-intel

# For NVIDIA
sudo pacman -S nvidia nvidia-utils
```

## Transitioning Development

If you were developing on Windows:

### Visual Studio → Linux
1. Code is now in `main.cpp` instead of `Final project.cpp`
2. Use any Linux editor: VS Code, CLion, Vim, etc.
3. Build with `make` instead of F5/Ctrl+Shift+B
4. Debug with gdb: `gdb ./particle_simulation`

### Recommended Linux IDEs
- **VS Code**: Cross-platform, similar to Visual Studio
- **CLion**: Full-featured C++ IDE (JetBrains)
- **Qt Creator**: Great for C++ development
- **Vim/Neovim**: Lightweight, powerful

### Source Control
The repository now includes:
- `.gitignore` - Excludes build artifacts
- Clean separation of source and build files

## Dual Boot Considerations

If running both Windows and Linux:

### Shared Configuration
Store `Parameters.txt` in a location accessible from both systems:
1. Create a FAT32 or NTFS partition
2. Mount it on Linux
3. Link or copy configuration files

### Separate Builds
Keep builds separate:
- Windows: `Final project.exe` in project root
- Linux: `particle_simulation` in project root (different binary)

## Getting Help

### Documentation
- `README.md` - Usage and features
- `INSTALL.md` - Installation details
- `OPTIMIZATION.md` - Performance tuning

### Community Resources
- Arch Wiki: https://wiki.archlinux.org/
- Endeavour OS Forum: https://forum.endeavouros.com/
- SDL2 Documentation: https://wiki.libsdl.org/

### Reporting Issues
If you find bugs or have suggestions, please report them in the repository's issue tracker.

## Summary

The Linux version maintains all functionality of the Windows version while adding:
- Better performance through hardware acceleration
- Modern build system
- Cross-platform compatibility
- Advanced compiler optimizations
- Comprehensive documentation

Your existing `Parameters.txt` configurations will work without modification!
