#include "shape/cube.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "context_manager.h"
#include "utils.h"

namespace graphics::shape {
int Cube::rotation_speed = OpenGLContext::getRefreshRate() * 2;
glm::quat Cube::base_rotation[3] = {glm::angleAxis(utils::PI_2<float>() / rotation_speed, glm::vec3(1, 0, 0)),
                                    glm::angleAxis(utils::PI_2<float>() / rotation_speed, glm::vec3(0, 1, 0)),
                                    glm::angleAxis(utils::PI_2<float>() / rotation_speed, glm::vec3(0, 0, 1))};

Cube::Cube(glm::vec3 _position) noexcept
    : position(_position), rotation(1, 0, 0, 0), rotation_progress(rotation_speed) {
  translation = glm::translate(glm::mat4(1.0f), position * scale);
}

void Cube::setupModel() noexcept {
  if (rotation_direction) {
    if (rotation_progress == 0) {
      rotation_direction = std::nullopt;
      rotation_progress = rotation_speed;
    } else {
      --rotation_progress;
      // TODO: Update rotation
      rotation = base_rotation[*rotation_direction] * rotation;
    }
  }
  // TODO: Update model matrix
  // Hint: mat4_cast, glMultMatrixf, value_ptr
  glm::mat4 model = glm::mat4_cast(rotation) * translation;
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
  // TODO: Render right face
  // Hint: glBegin, glColor3f, glNormal3f, glVertex3f, glEnd
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.0f, 0.0f);
  glNormal3f(1.0f, 0.0f, 0.0f);

  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glEnd();

  // Yellow, left
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 1.0f, 0.0f);
  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glEnd();

  // Blue, front
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(0.0f, 0.0f, 1.0f);
  glNormal3f(0.0f, 0.0f, 1.0f);

  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glEnd();

  // Magenta, back
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.0f, 1.0f);
  glNormal3f(0.0f, 0.0f, -1.0f);

  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glEnd();
}

void Cube::rotate(Axis axis) { rotation_direction = static_cast<int>(axis); }
}  // namespace graphics::shape
