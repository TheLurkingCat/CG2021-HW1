#include "shape/sphere.h"

#include <cmath>

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace graphics::shape {

Sphere::Sphere(float _radius, int _stacks, int _slices) noexcept : radius(_radius), stacks(_stacks), slices(_slices) {}

void Sphere::draw() const noexcept {
  float slice_step = static_cast<float>(2 * M_PI / slices);
  float stack_step = static_cast<float>(M_PI / stacks);
  // TODO: You should implement the sphere function by yourself,
  //       that is, you cannot use gluSphere() or something like that.
  // Hint: glBegin, GL_TRIANGLE_STRIP, glEnd, glNormal3f, glTexCoord2f, glVertex3f, parametric equation
  for (int i = 0; i <= slices; i++) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j <= stacks; j++) {
      float theta = j * stack_step;
      float phi = i * slice_step;

      float x = std::sin(theta) * std::cos(phi);
      float y = std::cos(theta);
      float z = std::sin(theta) * std::sin(phi);
      float u = 1 - static_cast<float>(i) / slices;
      float v = static_cast<float>(j) / stacks;

      glTexCoord2f(u, v);
      glNormal3f(x, y, z);
      glVertex3f(radius * x, radius * y, radius * z);

      x = std::sin(theta) * std::cos(phi + slice_step);
      z = std::sin(theta) * std::sin(phi + slice_step);
      u = 1 - static_cast<float>(i + 1) / slices;

      glTexCoord2f(u, v);
      glNormal3d(x, y, z);
      glVertex3f(radius * x, radius * y, radius * z);
    }
    glEnd();
  }
}
}  // namespace graphics::shape
