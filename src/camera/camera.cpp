#include "camera/camera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace graphics::camera {

Camera::Camera(glm::vec3 _position)
    : position(_position), up(0, 1, 0), front(0, 0, -1), right(1, 0, 0), projectionMatrix(), viewMatrix() {}

void Camera::initialize(float aspectRatio) {
  updateProjection(aspectRatio);
  updateView();
}
}  // namespace graphics::camera
