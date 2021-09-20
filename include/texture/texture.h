#pragma once
#include <filesystem>

#include <glad/gl.h>
#include <wuffs.h>

#include "utils.h"

namespace graphics::texture {
class Texture {
 public:
  // Shouldn't copy the texture
  MOVE_ONLY(Texture)
  virtual ~Texture();
  /// @brief Return current texture handle.
  GLuint getHandle() const noexcept { return handle; }
  /// @brief Convert to GLuint to use as handle
  explicit operator GLuint() const noexcept { return handle; };
  /**
   * @brief Bind this texture
   *
   * @param index Texture index, you have to pass a different index if you want to use multiple textures in the same
   * object.
   * (You don't need to change it when you doing your homework)
   */
  virtual void bind(GLuint index = 0) = 0;
  CONSTEXPR_VIRTUAL virtual GLenum getType() const noexcept = 0;
  CONSTEXPR_VIRTUAL virtual const char* getTypeName() const noexcept = 0;

 protected:
  Texture() noexcept;
  /// @brief Decode PNG file
  wuffs_aux::DecodeImageResult __loadpng(const std::filesystem::path& path);
  GLuint handle;
};
}  // namespace graphics::texture
