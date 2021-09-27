#pragma once

#include "shape/shape.h"

#include <glm/glm.hpp>

namespace graphics::shape {
class Cube : Shape {
 public:
  Cube() noexcept;
  void draw() const noexcept override;
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Cube"; }

private:
  glm::vec3 direction;
};

/* class CornerCube : Cube {
  enum class Direction { BTL, BTR, BDL, BDR, FTL, FTR, FDL, FDR };
 public:
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Corner Cube"; }
};

class SideCube : Cube {
  enum class Direction { TB, TR, TF, TL, LB, BR, RF, FL, DB, DR, DF, DL };
 public:
  CONSTEXPR_VIRTUAL const char* getTypeName() const noexcept override { return "Side Cube"; }
};*/
}  // namespace graphics::shape
