# NYCU CG2021 Homework 1 - TA Grader

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


### CMake

Use script/unzip.py to unzip all homeworks.

Build in release mode
```bash=
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel 8
bin/HW1
```

bin/HW1 is the sample code

bin/student-id is their homework

