#include <cmath>
#include <numeric>
#include <string>
#include <iostream>

#include <GLFW/glfw3.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#define WUFFS_IMPLEMENTATION
#include <wuffs.h>
#undef WUFFS_IMPLEMENTATION

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "camera/quat_camera.h"
#include "context_manager.h"
#include "layer/layer.h"
#include "shape/cube.h"
#include "shape/sphere.h"
#include "texture/texture2d.h"

// Cubes
std::vector<graphics::shape::Cube*> cubes;

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
  // There are three actions: press, release, hold
  if (action != GLFW_PRESS) return;
  switch (key) {
    case GLFW_KEY_ESCAPE:
      // Esc
      glfwSetWindowShouldClose(window, GL_TRUE);
      break;
    case GLFW_KEY_F:
      // f
      std::for_each(cubes.begin(), cubes.end(), [](graphics::shape::Cube* cube) {
        if (cube->getDirection().z == graphics::shape::Cube::Layer::Back) {
          cube->rotate(graphics::shape::Cube::Axis::X);
        }
      });
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
  OpenGLContext::createContext(21, GLFW_OPENGL_ANY_PROFILE);
  GLFWwindow* window = OpenGLContext::getWindow();
  glfwSetWindowTitle(window, "HW1");
  glfwSetKeyCallback(window, keyCallback);
  glfwSetFramebufferSizeCallback(window, resizeCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  OpenGLContext::printSystemInfo();
  OpenGLContext::enableDebugCallback();
  // Legacy OpenGL need these
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // TODO: Setup lights
  // Hint: glColorMaterial, glLightfv
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  float light_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
  float light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
  float light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  // Some parameters.
  int speed = OpenGLContext::getRefreshRate() / 4;
  int current_tick = 0;
  int body_speed = 28 * speed;
  int cycle = 360;
  int side = 3;
  float body_tick = 0;
  // Camera
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 4, 4));
  camera.initialize(OpenGLContext::getAspectRatio());
  glfwSetWindowUserPointer(window, &camera); 
  
  for (int i = 0; i < pow(side, 3); i++) {
    // Notice that the following corresponding to the enum { Front, Middle, Back } at cube.h
    // Minus 1 at the end to let the rotation easier
    int xAxis = i / pow(side, 2);
    int yAxis = (i - xAxis * pow(side, 2)) / side;
    int zAxis = i % side;
    cubes.push_back(new graphics::shape::Cube(glm::vec3(xAxis - 1, yAxis - 1, zAxis - 1)));
  }

  // Main rendering loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    camera.move(window);
    // Update simulation tick
    (++current_tick) %= cycle;
    body_tick = static_cast<float>(current_tick % body_speed) / body_speed;
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
    // Render sun, need to disable lighting since light source is actully 'inside' the sun.
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glRotatef(360 * body_tick, 0, 1, 0);

    for (auto cube : cubes) {
      cube->draw();
    }

    glEnable(GL_LIGHTING);
    // TODO: Maybe you need to put some glPopMatrix here depends on your implementation.
    glPopMatrix();
    // Some platform need explicit glFlush
    glFlush();
    glfwSwapBuffers(window);
  }

  return 0;
}
