#include "shape/cube.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"

namespace graphics::shape {
glm::quat Cube::rx = glm::angleAxis(utils::PI_2<float>(), glm::vec3(1, 0, 0));
glm::quat Cube::ry = glm::angleAxis(utils::PI_2<float>(), glm::vec3(0, 1, 0));
glm::quat Cube::rz = glm::angleAxis(utils::PI_2<float>(), glm::vec3(0, 0, 1));

Cube::Cube(glm::vec3 _direction) noexcept : direction(_direction), rotation(1, 0, 0, 0) {}

void Cube::setupModelView() const noexcept {
  glm::vec3 translate = direction * scale;
  glm::mat4 model = glm::mat4_cast(rotation) * glm::translate(glm::mat4(1), translate);
  glMultMatrixf(glm::value_ptr(model));
}

void Cube::draw() const noexcept {
  // Green, top
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(0.0f, 1.0f, 0.0f);
  glNormal3f(0.0f, 1.0f, 0.0f);

  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glEnd();

  // Orange, bottom
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.5f, 0.0f);
  glNormal3f(0.0f, -1.0f, 0.0f);

  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glEnd();

  // Red, right
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.0f, 0.0f);
  glNormal3f(0.0f, 0.0f, 1.0f);

  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glEnd();

  // Yellow, left
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 1.0f, 0.0f);
  glNormal3f(0.0f, -0.0f, -1.0f);

  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glEnd();

  // Blue, front
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(0.0f, 0.0f, 1.0f);
  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glEnd();

  // Magenta, back
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.0f, 1.0f);
  glNormal3f(1.0f, 0.0f, 0.0f);

  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glEnd();
}

void Cube::rotate(Axis axis) {
  switch (axis) {
    case Axis::X:
      rotation = rx * rotation;
      break;
    case Axis::Y:
      rotation = ry * rotation;
      break;
    case Axis::Z:
      rotation = rz * rotation;
      break;
  }
}
}  // namespace graphics::shape
