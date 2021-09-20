#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "camera/camera.h"

namespace graphics::camera {
class QuaternionCamera : public Camera {
 public:
  QuaternionCamera(glm::vec3 _position) : Camera(_position), rotation(1, 0, 0, 0) {}
  void move(GLFWwindow* window) override;
  void updateView() override;
  void updateProjection(float aspectRatio) override;

 private:
  glm::quat rotation;
  constexpr static float keyboardMoveSpeed = 10.0f;
  constexpr static float mouseMoveSpeed = 0.05f;
};
}  // namespace graphics::camera
