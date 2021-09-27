#pragma once

#include "shape/shape.h"

#include <glm/glm.hpp>

namespace graphics::shape {
class Cube : Shape {
 static float Unit;
 // Axis transform; used while doing layer-rotation
 static glm::mat3 xAxisRotate;
 static glm::mat3 yAxisRotate;
 static glm::mat3 zAxisRotate;

 public:
  enum Layer { Front = -1, Middle = 0, Back = 1 };
  enum Axis { X = 0, Y = 1, Z = 2 };

  Cube(glm::vec3 direction) noexcept;
  glm::vec3 getDirection() { return direction; };
  void draw() const noexcept override;
  void rotate(Axis axis);
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Cube"; }

private:
  glm::vec3 direction;
  void rotateX();
  void rotateY();
  void rotateZ();
};
}  // namespace graphics::shape
