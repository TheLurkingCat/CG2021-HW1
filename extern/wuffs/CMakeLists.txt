project(WUFFS
  VERSION         0.3
  DESCRIPTION     "Wrangling Untrusted File Formats Safely."
  HOMEPAGE_URL    "https:#github.com/google/wuffs"
  LANGUAGES       CXX
)

add_library(wuffs INTERFACE)
target_compile_definitions(wuffs
  INTERFACE WUFFS_CONFIG__MODULES
  INTERFACE WUFFS_CONFIG__MODULE__AUX__BASE
  INTERFACE WUFFS_CONFIG__MODULE__AUX__IMAGE
  INTERFACE WUFFS_CONFIG__MODULE__BASE
  # --- define these for PNG texture ---
  INTERFACE WUFFS_CONFIG__MODULE__ADLER32
  INTERFACE WUFFS_CONFIG__MODULE__CRC32
  INTERFACE WUFFS_CONFIG__MODULE__DEFLATE
  INTERFACE WUFFS_CONFIG__MODULE__PNG
  INTERFACE WUFFS_CONFIG__MODULE__ZLIB
  # --- define these for GIF texture ---
  # INTERFACEWUFFS_CONFIG__MODULE__LZW
  # INTERFACEWUFFS_CONFIG__MODULE__GIF
  # --- define this for BMP texture ---
  # INTERFACEWUFFS_CONFIG__MODULE__BMP
  # --- define this for WBMP texture ---
  # INTERFACEWUFFS_CONFIG__MODULE__WBMP
)
# Use c++17 as default
target_compile_features(wuffs INTERFACE cxx_std_17)
# No extensions
set_target_properties(wuffs PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(wuffs INTERFACE ${WUFFS_SOURCE_DIR}/include)
