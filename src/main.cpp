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

enum Axis { XAxis, YAxis, ZAxis };
int renderAxis = XAxis;

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
  // There are three actions: press, release, hold
  if (action != GLFW_PRESS) return;
  switch (key) {
    case GLFW_KEY_ESCAPE:
      // Esc
      glfwSetWindowShouldClose(window, GL_TRUE);
      break;
    case GLFW_KEY_X:
      // x
      renderAxis = XAxis;
      break;
    case GLFW_KEY_Y:
      // y
      renderAxis = YAxis;
      break;
    case GLFW_KEY_Z:
      // z
      renderAxis = ZAxis;
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
  float body_tick = 0;
  float TranslateUnit = 2.0f;
  float TranslateVector[] = {-TranslateUnit, 0, TranslateUnit};
  // Camera
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 4, 4));
  camera.initialize(OpenGLContext::getAspectRatio());
  glfwSetWindowUserPointer(window, &camera);
  // Cubes
  graphics::shape::Cube cubes[27];
  // Axis transform; used while doing layer-rotation
  glm::mat3 xAxisTransform = glm::mat3({1.0, 0, 0, 0, 1.0, 0, 0, 0, 1});
  glm::mat3 yAxisTransform = glm::mat3({0, 0, 1.0, 0, 1.0, 0, -1.0, 0, 0});
  glm::mat3 zAxisTransform = glm::mat3({0, -1.0, 0, 1.0, 0, 0, 0, 0, 1});
  // Layer
  graphics::layer::Layer F(xAxisTransform), S(xAxisTransform), B(xAxisTransform), T(yAxisTransform), E(yAxisTransform),
      D(yAxisTransform), L(zAxisTransform), M(zAxisTransform), R(zAxisTransform);
  F.setBlocks(std::begin({0, 1, 2, 3, 4, 5, 6, 7, 8}));
  S.setBlocks(std::begin({9, 10, 11, 12, 13, 14, 15, 16, 17}));
  B.setBlocks(std::begin({18, 19, 20, 21, 22, 23, 24, 25, 26}));
  L.setBlocks(std::begin({18, 9, 0, 21, 12, 3, 24, 15, 6}));
  M.setBlocks(std::begin({19, 10, 1, 22, 13, 4, 25, 16, 7}));
  R.setBlocks(std::begin({20, 11, 2, 23, 14, 5, 26, 17, 8}));
  T.setBlocks(std::begin({18, 19, 20, 9, 10, 11, 0, 1, 2}));
  E.setBlocks(std::begin({21, 22, 23, 12, 13, 14, 3, 4, 5}));
  D.setBlocks(std::begin({24, 25, 26, 15, 16, 17, 6, 7, 8}));

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

    if (renderAxis == 0) {
      glPushMatrix();
      glTranslatef(graphics::layer::Layer::TranslateUnit, 0, 0);
      glRotatef(360 * body_tick, 1, 0, 0);
      F.draw(cubes);
      glPopMatrix();

      S.draw(cubes);

      glPushMatrix();
      glTranslatef(-graphics::layer::Layer::TranslateUnit, 0, 0);
      B.draw(cubes);
      glPopMatrix();
    } else if (renderAxis == 1) {
      glPushMatrix();
      glTranslatef(0, graphics::layer::Layer::TranslateUnit, 0);
      glRotatef(360 * body_tick, 0, 1, 0);
      L.draw(cubes);
      glPopMatrix();

      M.draw(cubes);

      glPushMatrix();
      glTranslatef(0, -graphics::layer::Layer::TranslateUnit, 0);
      R.draw(cubes);
      glPopMatrix();
    } else if (renderAxis == 2) {
      glPushMatrix();
      glTranslatef(0, 0, graphics::layer::Layer::TranslateUnit);
      glRotatef(360 * body_tick, 0, 0, 1);
      T.draw(cubes);
      glPopMatrix();
      E.draw(cubes);

      glPushMatrix();
      glTranslatef(0, 0, -graphics::layer::Layer::TranslateUnit);
      D.draw(cubes);
      glPopMatrix();
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
