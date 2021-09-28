#pragma once
#include <optional>

#include "shape/shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace graphics::shape {
class Cube : public Shape {
  static constexpr float scale = 2.05f;
  static int rotation_speed;
  static glm::quat base_rotation[3];

  // Axis transform; used while doing layer-rotation

 public:
  enum class Axis { X = 0, Y = 1, Z = 2 };

  explicit Cube(glm::vec3 position) noexcept;
  glm::vec3 getPosition() const noexcept { return rotation * position; }
  float getPosition(Axis axis) const noexcept { return (rotation * position)[static_cast<int>(axis)]; }
  bool isIdle() const noexcept { return !rotation_direction.has_value(); }

  void setupModel() noexcept override;
  void draw() const noexcept override;
  void animateRotation() const;
  void rotate(Axis axis);
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Cube"; }

 private:
  std::optional<int> rotation_direction;
  int rotation_progress;
  glm::vec3 position;
  glm::mat4 translation;
  glm::quat rotation;
};
}  // namespace graphics::shape
