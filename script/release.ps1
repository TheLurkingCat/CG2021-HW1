if (!(Test-Path -Path "src")) {
  cd ..
}

if (!(Test-Path -Path "src")) {
  Write-Output "Please run this script in project root folder."
  exit 1
}

$compressfiles = `
"extern/glad" `
"extern/glfw/CMake" `
"extern/glfw/deps/mingw" `
"extern/glfw/deps/vs2008" `
"extern/glfw/include" `
"extern/glfw/src" `
"extern/glfw/LICENSE.md" `
"extern/glfw/CMakeLists.txt" `
"extern/glm/cmake" `
"extern/glm/glm" `
"extern/glm/CMakeLists.txt" `
"extern/glm/copying.txt" `
"script/pack.ps1" `
"script/pack.sh" `
"cmake" `
"vs2019/HW1.sln" `
"vs2019/HW1" `
"vs2019/glfw" `
"include" `
"src" `
".clang-format" `
"CMakeLists.txt" `
"README.md"

$compress = @{
  Path = $compressfiles
  CompressionLevel = "Optimal"
  DestinationPath = "HW1.zip"
}
Compress-Archive @compress
