#pragma once
#include <filesystem>

#include "texture.h"
#include "utils.h"

namespace graphics::texture {
class Texture2D final : public Texture {
 public:
  /// @brief Load a texture from a PNG image.
  void loadPNG(const std::filesystem::path& path);
  void bind(GLuint index = 0) override;
  CONSTEXPR_VIRTUAL GLenum getType() const noexcept override { return GL_TEXTURE_2D; }
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "TEXTURE_2D"; }

 private:
  /**
   * @brief Setup texture by given parameters.
   *
   * @param image_width The width of the image.
   * @param image_height The height of the image.
   * @param image_data The pixel data of the image (BGRA format).
   */
  void loadTexture(int image_width, int image_height, uint8_t* image_data);
};
}  // namespace graphics::texture
