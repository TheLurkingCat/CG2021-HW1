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

// Unnamed namespace
namespace {
bool is_auto_rotate = false;
std::vector<std::unique_ptr<graphics::shape::Cube>> cubes;
}  // namespace

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
  // Use smart pointers, not raw pointers
  using CubePTR = std::unique_ptr<graphics::shape::Cube>;
  // There are three Axis: X, Y, Z
  using Axis = graphics::shape::Axis;
  // There are three actions: press, release, hold
  if (action != GLFW_PRESS) return;
  if (key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return;
  }
  // Check all cubes are not rotating
  bool idle = std::all_of(cubes.begin(), cubes.end(), [](CubePTR& cube) { return cube->isIdle(); });
  if (!idle) return;
  // TODO: Detect key-events, perform rotation
  // Hint: Key  (https://www.glfw.org/docs/3.3/group__keys.html)
  switch (key) {
    case GLFW_KEY_F:
      // f
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::Z) == 1) {
          cube->rotate(Axis::Z);
        }
      });
      break;
    case GLFW_KEY_C:
      // c
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::Z) == 0) {
          cube->rotate(Axis::Z);
        }
      });
      break;
    case GLFW_KEY_B:
      // b
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::Z) == -1) {
          cube->rotate(Axis::Z);
        }
      });
      break;
    case GLFW_KEY_U:
      // u
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::Y) == 1) {
          cube->rotate(Axis::Y);
        }
      });
      break;
    case GLFW_KEY_E:
      // e
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::Y) == 0) {
          cube->rotate(Axis::Y);
        }
      });
      break;
    case GLFW_KEY_G:
      // g
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::Y) == -1) {
          cube->rotate(Axis::Y);
        }
      });
      break;
    case GLFW_KEY_L:
      // l
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::X) == -1) {
          cube->rotate(Axis::X);
        }
      });
      break;
    case GLFW_KEY_M:
      // m
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::X) == 0) {
          cube->rotate(Axis::X);
        }
      });
      break;
    case GLFW_KEY_R:
      // r
      std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) {
        if (cube->getPosition(Axis::X) == 1) {
          cube->rotate(Axis::X);
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
        std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) { cube->rotate(Axis::X); });
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
        std::for_each(cubes.begin(), cubes.end(), [](CubePTR& cube) { cube->rotate(Axis::Z); });
      }
      break;
    default:
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
#ifndef NDEBUG
  OpenGLContext::printSystemInfo();
  // This is useful if you want to debug your OpenGL API calls.
  OpenGLContext::enableDebugCallback();
#endif
  // TODO: Setup lights
  //       1. You should enable some OpenGL features (e.g. GL_LIGHTING)
  //       2. Setup light's property (e.g. GL_POSITION)
  // Hint and Reference:
  //       glEnable        (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glEnable.xml)
  //       glColorMaterial (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glColorMaterial.xml)
  //       glLight         (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLight.xml)
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  const float light_pos[] = {0.0f, 1.0f, 2.0f, 0.0f};
  const float light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  const float light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  // Some parameters.
  int speed = OpenGLContext::getRefreshRate() * 10;
  int current_tick = 0;
  float body_tick = 0;
  // Setup camera.
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 0, 10));
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
    // Polling events.
    glfwPollEvents();
    camera.move(window);
    // If the cube us rotating, add dtheta to current rotation angle.
    if (is_auto_rotate) {
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
    // Rotate whole cube
    glRotatef(360 * body_tick, 0, 1, 0);
    // TODO: Render Rubik's cube
    //       1. Iterate through all cube in cubes.
    //       2. For each cube, call cube->setupModel() and cube->draw().
    //       2. You can use glPushMatrix, glPopMatrix to 'cache' current matrix.
    // Hint:
    //       glPushMatrix/glPopMatrix   (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml)
    for (const auto& cube : cubes) {
      glPushMatrix();
      cube->setupModel();
      cube->draw();
      glPopMatrix();
    }
#ifdef __APPLE__
    // Some platform need explicit glFlush
    glFlush();
#endif
    glfwSwapBuffers(window);
  }
  return 0;
}
