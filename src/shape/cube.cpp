#include "shape/cube.h";

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace graphics::shape {
float Cube::Unit = 2.0f;
glm::mat3 Cube::xAxisRotate = glm::mat3({1.0, 0, 0, 0, 0, -1.0, 0, 1.0, 0});
glm::mat3 Cube::zAxisRotate = glm::mat3({0, 0, 1.0, 0, 1.0, 0, -1.0, 0, 0});
glm::mat3 Cube::yAxisRotate = glm::mat3({0, -1.0, 0, 1.0, 0, 0, 0, 0, 1});

Cube::Cube(glm::vec3 _direction) noexcept : direction(_direction), rotation(glm::vec3(0, 0, 0)) {}
void Cube::draw() const noexcept {
  glPushMatrix();

  glm::vec3 translate = direction * Unit;
  glTranslatef(translate.x, translate.y, translate.z);
  glRotatef(rotation.x, 1, 0, 0);
  glRotatef(rotation.y, 0, 1, 0);
  glRotatef(rotation.z, 0, 0, 1);

  glBegin(GL_QUADS);

  // Green, top
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);

  // Orange, bottom
  glColor3f(1.0f, 0.5f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);

  // Red, right
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);

  // Yellow, left
  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);

  // Blue, front
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);

  // Magenta, back
  glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);

  glEnd();  // End of drawing color-cube
  glPopMatrix();
}
void Cube::rotate(Axis axis) {
  if (axis == Axis::X) {
    rotateX();
  } else if (axis == Axis::Y) {
    rotateY();
  } else if (axis == Axis::Z) {
    rotateZ();
  }
}
void Cube::rotateX() {
  direction = xAxisRotate * direction;
  float newXdeg = rotation.x >= 270 ? 0 : (rotation.x + 90);
  rotation = glm::vec3(newXdeg, rotation.y, rotation.z);
}
void Cube::rotateY() {
  direction = zAxisRotate * direction;
  float newYdeg = rotation.y >= 270 ? 0 : (rotation.y + 90);
  rotation = glm::vec3(rotation.x, newYdeg, rotation.z);
}
void Cube::rotateZ() {
  direction = yAxisRotate * direction;
  float newZdeg = rotation.z >= 270 ? 0 : (rotation.z + 90);
  rotation = glm::vec3(rotation.x, rotation.y, newZdeg);
}
}  // namespace graphics::shape