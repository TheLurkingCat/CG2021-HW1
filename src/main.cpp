#include <cmath>
#include <numeric>
#include <string>

#include <GLFW/glfw3.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define WUFFS_IMPLEMENTATION
#include <wuffs.h>
#undef WUFFS_IMPLEMENTATION

#include "camera/quat_camera.h"
#include "context_manager.h"
#include "shape/sphere.h"
#include "texture/texture2d.h"

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
  // There are three actions: press, release, hold
  if (action != GLFW_PRESS) return;
  switch (key) {
    case GLFW_KEY_ESCAPE:
      // Esc
      glfwSetWindowShouldClose(window, GL_TRUE);
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
  // Legacy OpenGL need this
  glEnable(GL_TEXTURE_2D);
  // Some parameters.
  int speed = OpenGLContext::getRefreshRate() / 5;
  // Sphere
  graphics::shape::Sphere earth(1, 180, 360), moon(0.273, 36, 72);

  graphics::texture::Texture2D earth_texture, moon_texture;
  moon_texture.loadPNG("../assets/texture/moon.png");
  earth_texture.loadPNG("../assets/texture/earth.png");

  int current_tick = 0;
  int earth_speed = 1 * speed, moon_speed = 28 * speed;
  int cycle = std::lcm(earth_speed, moon_speed);
  float earth_tick = 0, moon_tick = 0;
  // Camera
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 0, 10));
  camera.initialize(OpenGLContext::getAspectRatio());
  glfwSetWindowUserPointer(window, &camera);
  // Main rendering loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    camera.move(window);
    // Update simulation tick
    (++current_tick) %= cycle;
    earth_tick = static_cast<float>(current_tick % earth_speed) / earth_speed;
    moon_tick = static_cast<float>(current_tick % moon_speed) / moon_speed;
    // GL_XXX_BIT can simply "OR" together to use.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(camera.getProjectionMatrix());
    // ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(camera.getViewMatrix());
    // Render Earth
    glPushMatrix();
    glRotatef(-23.5, 0, 0, 1);
    glRotatef(360.0f * earth_tick, 0, 1, 0);
    earth_texture.bind();
    earth.draw();
    glPopMatrix();
    // Render Moon
    glPushMatrix();
    glRotatef(360.0f * moon_tick, 0, 1, 0);
    glTranslatef(1.5, 0, 0);
    moon_texture.bind();
    moon.draw();
    glPopMatrix();

    // Some platform need explicit glFlush
    glFlush();
    glfwSwapBuffers(window);
  }

  return 0;
}
