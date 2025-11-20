# Quick Start Guide

Get the particle simulation running in 3 simple steps!

## For Endeavour OS / Arch Linux Users

### Step 1: Install Dependencies
```bash
sudo pacman -S sdl2 sdl2_ttf gcc make
```

### Step 2: Build
```bash
./build.sh
```

### Step 3: Run
```bash
./particle_simulation
```

**That's it!** Press ESC to exit.

---

## Customization

Edit `Parameters.txt` before running to change the simulation:

```bash
nano Parameters.txt
```

### Quick Settings

**For a lot of particles:**
```
procent: 50
situation: 0
```

**For walls and bouncing:**
```
borders: 1
infinity: 0
```

**To see grid and count:**
```
lines: 1
masscnt: 1
```

**For slower/smoother animation:**
```
sleeptime: 20
```

---

## Scenarios

Change `situation: X` to try different setups:

- `0` - Random particles everywhere
- `1` - Concentrated region
- `2-8` - Various barrier configurations

---

## Troubleshooting

**Build fails?**
```bash
sudo pacman -S base-devel
```

**Font warning?** (Optional - text won't show)
```bash
sudo pacman -S ttf-dejavu
```

**Want more help?**
- Read `README.md` for detailed info
- See `INSTALL.md` for installation help
- Check `MIGRATION.md` if coming from Windows version

---

## One-Line Install & Run

```bash
sudo pacman -S sdl2 sdl2_ttf gcc make && ./build.sh && ./particle_simulation
```

Enjoy! 🎨
