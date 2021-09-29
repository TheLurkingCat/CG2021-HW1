#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera/quat_camera.h"
#include "context_manager.h"
#include "shape/cube.h"

bool is_auto_rotate = false;
std::optional<int> rotation_direction = std::nullopt;
// Cubes
std::vector<std::unique_ptr<graphics::shape::Cube>> cubes;

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
  using CubePTR = std::unique_ptr<graphics::shape::Cube>;
  using Axis = graphics::shape::Cube::Axis;
  // There are three actions: press, release, hold
  if (action != GLFW_PRESS) return;
  if (key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return;
  }
  bool idle = std::all_of(cubes.begin(), cubes.end(), [](CubePTR& cube) { return cube->isIdle(); });
  if (!idle) return;
  // TODO: Detect key-events
  switch (key) {
    case GLFW_KEY_F:
      // f
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().x < -0.5) {
          cube->rotate(Axis::X);
        }
      });
      break;
    case GLFW_KEY_C:
      // c
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().x == 0) {
          cube->rotate(Axis::X);
        }
      });
      break;
    case GLFW_KEY_B:
      // b
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().x > 0.5) {
          cube->rotate(Axis::X);
        }
      });
      break;
    case GLFW_KEY_U:
      // u
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().y > 0.5) {
          cube->rotate(Axis::Y);
        }
      });
      break;
    case GLFW_KEY_E:
      // e
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().y == 0.0) {
          cube->rotate(Axis::Y);
        }
      });
      break;
    case GLFW_KEY_G:
      // g
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().y < -0.5) {
          cube->rotate(Axis::Y);
        }
      });
      break;
    case GLFW_KEY_L:
      // l
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().z < -0.5) {
          cube->rotate(Axis::Z);
        }
      });
      break;
    case GLFW_KEY_M:
      // m
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().z == 0.0) {
          cube->rotate(Axis::Z);
        }
      });
      break;
    case GLFW_KEY_R:
      // r
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition().z > 0.5) {
          cube->rotate(Axis::Z);
        }
      });
      break;
    case GLFW_KEY_Q:
      // q
      is_auto_rotate = !is_auto_rotate;
      break;
    case GLFW_KEY_X:
      // x
      if (!is_auto_rotate) {
        std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) { cube->rotate(Axis::Z); });
      }
      break;
    case GLFW_KEY_Y:
      // y
      if (!is_auto_rotate) {
        std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) { cube->rotate(Axis::Y); });
      }
      break;
    case GLFW_KEY_Z:
      // z
      if (!is_auto_rotate) {
        std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) { cube->rotate(Axis::X); });
      }
      break;
  }
}

void resizeCallback(GLFWwindow* window, int width, int height) {
  OpenGLContext::framebufferResizeCallback(window, width, height);
  auto ptr = static_cast<graphics::camera::Camera*>(glfwGetWindowUserPointer(window));
  if (ptr != nullptr) {
    ptr->updateProjection(OpenGLContext::getAspectRatio());
  }
}

int main() {
  // Initialize OpenGL context, details are wrapped in class.
  OpenGLContext::createContext(41, GLFW_OPENGL_COMPAT_PROFILE);
  GLFWwindow* window = OpenGLContext::getWindow();
  glfwSetWindowTitle(window, "HW1");
  glfwSetKeyCallback(window, keyCallback);
  glfwSetFramebufferSizeCallback(window, resizeCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  OpenGLContext::printSystemInfo();
#ifndef NDEBUG
  OpenGLContext::enableDebugCallback();
#endif
  // Legacy OpenGL need these
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // TODO: Setup lights
  // Hint: glColorMaterial, glLightfv
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  float light_pos[] = {0.0f, 1.0f, 1.0f, 0.0f};
  float light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
  float light_diffuse[] = {0.75f, 0.75f, 0.75f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  // Some parameters.
  int speed = OpenGLContext::getRefreshRate() * 10;
  int current_tick = 0;
  float body_tick = 0.25;
  // Camera
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 4, 4));
  camera.initialize(OpenGLContext::getAspectRatio());
  glfwSetWindowUserPointer(window, &camera);

  // Generate all mini-cubes
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      for (int k = -1; k <= 1; ++k) {
        cubes.emplace_back(std::make_unique<graphics::shape::Cube>(glm::vec3(i, j, k)));
      }
    }
  }

  // Main rendering loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    camera.move(window);

    if (is_auto_rotate) {
      // Update simulation tick
      (++current_tick) %= speed;
      body_tick = static_cast<float>(current_tick) / speed;
    }

    // GL_XXX_BIT can simply "OR" together to use.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(camera.getProjectionMatrix());
    // ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(camera.getViewMatrix());
    // Light position needs to multiply with view matrix, but not model matrix
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glPushMatrix();
    glRotatef(360 * body_tick, 0, 1, 0);
    // TODO: Render Rubik's cube
    // Hint: glPushMatrix, glPopMatrix
    for (const auto& cube : cubes) {
      glPushMatrix();
      cube->setupModel();
      cube->draw();
      glPopMatrix();
    }
    glPopMatrix();
#ifdef __APPLE__
    // Some platform need explicit glFlush
    glFlush();
#endif
    glfwSwapBuffers(window);
  }
  return 0;
}
