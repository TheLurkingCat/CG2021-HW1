#include "camera/quat_camera.h"

namespace graphics::camera {
void QuaternionCamera::move(GLFWwindow* window) {
  bool ismoved = false;
  // Calculate dt
  static float lastFrameTime = static_cast<float>(glfwGetTime());
  float currentFrameTime = static_cast<float>(glfwGetTime());
  float deltaTime = currentFrameTime - lastFrameTime;
  lastFrameTime = currentFrameTime;
  float keyboardspeed = deltaTime * keyboardMoveSpeed;
  float mousespeed = deltaTime * mouseMoveSpeed;
  // Mouse part
  static double lastx = 0, lasty = 0;
  if (lastx == 0 && lasty == 0) {
    glfwGetCursorPos(window, &lastx, &lasty);
  } else {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    float dx = mousespeed * static_cast<float>(xpos - lastx);
    float dy = mousespeed * static_cast<float>(lasty - ypos);
    lastx = xpos;
    lasty = ypos;
    if (dx != 0 || dy != 0) {
      ismoved = true;
      glm::quat rx(glm::angleAxis(dx, glm::vec3(0, -1, 0)));
      glm::quat ry(glm::angleAxis(dy, glm::vec3(1, 0, 0)));
      rotation = rx * rotation * ry;
    }
  }
  // Keyboard part
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    position += front * keyboardspeed;
    ismoved = true;
  } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    position -= front * keyboardspeed;
    ismoved = true;
  } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    position -= right * keyboardspeed;
    ismoved = true;
  } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    position += right * keyboardspeed;
    ismoved = true;
  }
  // Update view matrix if moved
  if (ismoved) {
    updateView();
  }
}

void QuaternionCamera::updateView() {
  front = rotation * glm::vec3(0, 0, -1);
  up = rotation * glm::vec3(0, 1, 0);
  right = glm::cross(front, up);
  viewMatrix = glm::lookAt(position, position + front, up);
}

void QuaternionCamera::updateProjection(float aspectRatio) {
  projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 1000.0f);
}
}  // namespace graphics::camera
