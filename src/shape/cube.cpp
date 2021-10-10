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
    : rotation_progress(rotation_speed),
      position(_position),
      translation(glm::translate(glm::identity<glm::mat4>(), position * scale)),
      rotation(glm::identity<glm::quat>()) {}

void Cube::setupModel() noexcept {
  if (rotation_direction) {
    if (rotation_progress == 0) {
      rotation_direction = std::nullopt;
      rotation_progress = rotation_speed;
    } else {
      --rotation_progress;
      // TODO: Update rotation
      // Hint: rotation_direction is std::optional, you can treat it as a pointer like object.
      //   use *rotation_direction to access the value, and rotation_direction.has_value() to check if it is 'NULL'
      //   https://en.cppreference.com/w/cpp/utility/optional
    }
  }
  // TODO: Update model matrix
  // Hint: glMultMatrix  (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glMultMatrix.xml)
  // Note:
  //   1. How to transform quaternion into glm::mat4 rotation_matrix?
  //     -> glm::mat4 rotation_matrix = glm::mat4_cast(rotation)
  //   2. How to access float* pointer of glm::mat4 matrix?
  //     -> const float * ptr = glm::value_ptr(matrix)
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
  // TODO: Render other 5 face
  //       1. Setup color
  //       2. Setup normal
  //       3. Setup vertices
  //       You must use one of these enum in glBegin call (No GL_QUADS)
  //       GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY
  // Hint:
  //       glBegin/glEnd  (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glBegin.xml)
  //       glColor        (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glColor.xml)
  //       glNormal       (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glNormal.xml)
  //       glVertex       (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glVertex.xml)
}

void Cube::rotate(Axis axis) { rotation_direction = static_cast<int>(axis); }
}  // namespace graphics::shape
