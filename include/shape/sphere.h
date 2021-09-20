#pragma once
#include "shape/shape.h"

namespace graphics::shape {
class Sphere : Shape {
 public:
  Sphere(float radius, int stacks, int slices) noexcept;
  void draw() const noexcept override;
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Sphere"; }

 private:
  float radius;
  int stacks;
  int slices;
};
}  // namespace graphics::shape
