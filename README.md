# CHIP-8 Emulator

This project implements a simple CHIP‑8 emulator written in C++20. Video and keyboard interaction are provided through [SDL2](https://www.libsdl.org/). The source code is split into a small collection of headers and source files with CMake build support.

# Demo

https://github.com/user-attachments/assets/f5c827ad-1ed1-4620-a5d4-5bcc7bd3babc

## Requirements

- **CMake** 3.16 or newer
- **C++20** compatible compiler (tested with GCC 13)
- **SDL2** development libraries
- A POSIX like environment (Linux, macOS) or Windows with a working C++ toolchain and SDL2.

## Building

1. Install the SDL2 development package for your system.
   - On Debian/Ubuntu: `sudo apt-get install libsdl2-dev`
2. Generate the build files and compile:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

The resulting binary `CHIP_8` will be located in the `build` directory.

## Running

Execute the emulator with three arguments:

```bash
./CHIP_8 <Scale> <CycleDelay> <ROM>
```

- `Scale` – integer factor used to enlarge the 64x32 CHIP‑8 display.
- `CycleDelay` – delay in milliseconds between CPU cycles (useful to slow down the emulation).
- `ROM` – path to a CHIP‑8 ROM file.

Example:

```bash
./CHIP_8 10 2 ../roms/PONG.ch8
```

You can get more games following this link -> https://github.com/kripod/chip8-roms

## Key Mapping

The emulator maps your keyboard to the CHIP‑8 hexadecimal keypad as follows:

```
1 2 3 4       -> 1 2 3 C
Q W E R       -> 4 5 6 D
A S D F       -> 7 8 9 E
Z X C V       -> A 0 B F
```

Use `Esc` to exit the emulator window.

## Project Structure

- `main.cpp` – program entry point; sets up the platform, loads the ROM and runs the emulation loop.
- `include/` – public headers for the emulator core and helper classes.
- `src/` – implementation files for the CHIP‑8 CPU, opcode dispatcher and instruction set.
- `helpers/` – small utility headers (type aliases, font data and constants).
- `CMakeLists.txt` – build configuration.

Fonts for the built‑in hexadecimal characters are defined in `helpers/fonts.h` and are loaded into memory on start‑up.

## Acknowledgments

This emulator was inspired by these excellent references:

- <https://austinmorlan.com/posts/chip8_emulator/>
- <http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#memmap>

Many thanks to the authors for their detailed guides.

## License

This repository contains code © Davio‑2002. See source files for individual license information.
