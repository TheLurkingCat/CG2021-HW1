#pragma once
#include "shape/cube.h";
#include "utils.h"

#include <glm/glm.hpp>

namespace graphics::layer {
class Layer {

 public:
  Layer(glm::mat3 axisTransformMatrix);
  static const float TranslateUnit;
  static const float TranslateVector[];
  void draw(graphics::shape::Cube cubes[27]);
  int* getBlocks();
  void rotate();
  void setBlocks(const int blocks[9]);

 private:
  int blocks[9];
  int degCounter;
  glm::mat3 axisTransformMatrix;
};
}  // namespace graphics::layer
