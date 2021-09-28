#pragma once

#include "shape/shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace graphics::shape {
class Cube : public Shape {
  static constexpr float scale = 2.1f;
  static glm::quat rx;
  static glm::quat ry;
  static glm::quat rz;
  // Axis transform; used while doing layer-rotation

 public:
  enum Layer { Front = -1, Middle = 0, Back = 1 };
  enum class Axis { X = 0, Y = 1, Z = 2 };

  explicit Cube(glm::vec3 direction) noexcept;
  glm::vec3 getDirection() { return rotation * direction; }
  void setupModelView() const noexcept override;
  void draw() const noexcept override;
  void rotate(Axis axis);
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Cube"; }

 private:
  glm::vec3 direction;
  glm::quat rotation;
};
}  // namespace graphics::shape
