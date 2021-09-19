#!/bin/bash
zip -r9 HW0.zip \
extern/glad \
extern/glfw/CMake \
extern/glfw/deps/mingw \
extern/glfw/deps/vs2008 \
extern/glfw/include \
extern/glfw/src \
extern/glfw/LICENSE.md \
extern/glfw/CMakeLists.txt \
extern/glm/cmake \
extern/glm/glm \
extern/glm/CMakeLists.txt \
extern/glm/copying.txt \
extern/wuffs
cmake \
include \
src \
.clang-format \
CMakeLists.txt \
README.md

