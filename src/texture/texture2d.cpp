#include "texture/texture2d.h"
#include <utility>

#include <wuffs.h>

namespace graphics::texture {

void Texture2D::loadPNG(const std::filesystem::path& path) {
  wuffs_aux::DecodeImageResult result = __loadpng(path);
  int width = static_cast<int>(result.pixbuf.pixcfg.width());
  int height = static_cast<int>(result.pixbuf.pixcfg.height());
  uint8_t* data = result.pixbuf.plane(0).ptr;
  loadTexture(width, height, data);
}

void Texture2D::bind(GLuint index) {
  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture2D::loadTexture(int image_width, int image_height, uint8_t* image_data) {
  int mipmap_level = utils::log2(std::max(image_width, image_height));
  glBindTexture(GL_TEXTURE_2D, handle);
  // TODO: Setup texture
  // Hint: image_data is in BGRA format, so you will use GL_BGRA somewhere
  // Hint: image_data is in uint8_t format(0-255), so you will use GL_UNSIGNED_BYTE somewhere
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexStorage2D(GL_TEXTURE_2D, mipmap_level, GL_RGBA8, image_width, image_height);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image_width, image_height, GL_BGRA, GL_UNSIGNED_BYTE, image_data);
  glGenerateMipmap(GL_TEXTURE_2D);
  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}
}  // namespace graphics::texture
