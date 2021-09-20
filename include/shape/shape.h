#pragma once

#include "utils.h"

namespace graphics::shape {
class Shape {
 public:
  virtual ~Shape() = default;
  virtual void draw() const noexcept = 0;
  CONSTEXPR_VIRTUAL virtual const char* getTypeName() const noexcept = 0;
};
}  // namespace graphics::shape