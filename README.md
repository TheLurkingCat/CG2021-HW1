# NYCU CG2021 Homework 1

[![release](https://github.com/TheLurkingCat/CG2021-HW1/actions/workflows/build.yml/badge.svg?branch=release&event=push)](https://github.com/TheLurkingCat/CG2021-HW1/actions/workflows/build.yml)

## Dependencies

- [glad](https://github.com/Dav1dde/glad)
- [glfw](https://github.com/glfw/glfw)
- [glm](https://github.com/g-truc/glm)

### Dependencies for Windows

Visual Studio

### Dependencies for macOS

Xcode

### Dependencies for Unix-like systems other than macOS with X11

On *Debian* and derivatives like *Ubuntu* and *Linux Mint*

`sudo apt install xorg-dev`

On *Fedora* and derivatives like *Red Hat*

`sudo dnf install libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel`

On *FreeBSD*

`pkg install xorgproto`

## Build instruction

### Clone the repository

`git clone --recurse-submodules -j8 https://github.com/TheLurkingCat/CG2021-HW1.git`

### CMake

Build in release mode
```bash=
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel 8
bin/HW1
```

Build in debug mode
```bash=
cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --parallel 8
bin/HW1
```

### Visual Studio 2019

- Open `vs2019/HW1.sln`
- Select config then build (CTRL+SHIFT+B)
- Use F5 to debug or CTRL+F5 to run.
