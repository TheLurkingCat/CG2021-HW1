#include "texture/texture.h"

#include <fstream>
#include <vector>

namespace graphics::texture {

Texture::Texture() noexcept : handle(0) { glGenTextures(1, &handle); }

Texture::~Texture() { glDeleteTextures(1, &handle); }

wuffs_aux::DecodeImageResult Texture::__loadpng(const std::filesystem::path& path) {
  std::ifstream image_file(path, std::ifstream::binary);
  if (!image_file) THROW_EXCEPTION(std::runtime_error, "Cannot open file: " + path.string());
  const std::vector<char> buffer((std::istreambuf_iterator<char>(image_file)), std::istreambuf_iterator<char>());
  image_file.close();

  wuffs_aux::DecodeImageCallbacks callbacks;
  wuffs_aux::sync_io::MemoryInput input(buffer.data(), buffer.size());
  wuffs_aux::DecodeImageResult res = wuffs_aux::DecodeImage(callbacks, input);

  if (!res.pixbuf.pixcfg.pixel_format().is_interleaved()) THROW_EXCEPTION(std::runtime_error, "Non-interleaved pixbuf");
  wuffs_base__table_u8 tab = res.pixbuf.plane(0);
  if (tab.width != tab.stride) THROW_EXCEPTION(std::runtime_error, "Could not allocate tight pixbuf");
  if (res.error_message.empty())
    return res;
  else
    THROW_EXCEPTION(std::runtime_error, res.error_message);
}
}  // namespace graphics::texture
