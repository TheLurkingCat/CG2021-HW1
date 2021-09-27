#include "shape/cube.h";

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace graphics::shape {
float Cube::Unit = 2.0f;
glm::mat3 Cube::xAxisRotate = glm::mat3({1.0, 0, 0, 0, 1.0, 0, 0, 0, 1});
glm::mat3 Cube::yAxisRotate = glm::mat3({0, -1.0, 0, 1.0, 0, 0, 0, 0, 1});
glm::mat3 Cube::zAxisRotate = glm::mat3({0, 0, 1.0, 0, 1.0, 0, -1.0, 0, 0});

Cube::Cube(glm::vec3 _direction) noexcept : direction(_direction) {}
void Cube::draw() const noexcept {
  glPushMatrix();

  glm::vec3 translate = direction * Unit;
  glTranslatef(translate.x, translate.y, translate.z);

  glBegin(GL_QUADS);

  if (direction.y == Layer::Back) {
    glColor3f(0.0f, 1.0f, 0.0f);  // Green
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
  }

  if (direction.y == Layer::Front) {
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
  }

  if (direction.z == Layer::Back) {
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
  }

  if (direction.z == Layer::Front) {
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
  }

  if (direction.x == Layer::Front) {
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
  }

  if (direction.x == Layer::Back) {
    glColor3f(1.0f, 0.0f, 1.0f);  // Magenta
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
  }

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
void Cube::rotateX() { direction = xAxisRotate * direction; }
void Cube::rotateY() { direction = yAxisRotate * direction; }
void Cube::rotateZ() { direction = zAxisRotate * direction; }
}  // namespace graphics::shape