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

#ifdef _MSC_VER
#pragma warning(push, 0)
#define WUFFS_IMPLEMENTATION
#include <wuffs.h>
#undef WUFFS_IMPLEMENTATION
#pragma warning(pop)
#endif

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
  // Spheres
  graphics::shape::Sphere sun(1.0f, 180, 360), earth(0.2f, 90, 180), moon(0.0546f, 36, 72);
  // Textures
  graphics::texture::Texture2D sun_texture, earth_texture, moon_texture;
  sun_texture.loadPNG("../assets/texture/sun.png");
  earth_texture.loadPNG("../assets/texture/earth.png");
  moon_texture.loadPNG("../assets/texture/moon.png");
  // Some parameters.
  int speed = OpenGLContext::getRefreshRate() / 4;
  int current_tick = 0;
  int earth_day_speed = 1 * speed;
  int moon_speed = 28 * speed;
  int sun_speed = moon_speed;
  int earth_year_speed = 365 * speed;
  int cycle = std::lcm(std::lcm(earth_day_speed, moon_speed), earth_year_speed);
  float earth_year_tick = 0, earth_day_tick = 0, moon_tick = 0, sun_tick = 0;
  // Camera
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 0, 4));
  camera.initialize(OpenGLContext::getAspectRatio());
  glfwSetWindowUserPointer(window, &camera);
  // Main rendering loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    camera.move(window);
    // Update simulation tick
    (++current_tick) %= cycle;
    sun_tick = static_cast<float>(current_tick % sun_speed) / sun_speed;
    earth_year_tick = static_cast<float>(current_tick % earth_year_speed) / earth_year_speed;
    earth_day_tick = static_cast<float>(current_tick % earth_day_speed) / earth_day_speed;
    moon_tick = static_cast<float>(current_tick % moon_speed) / moon_speed;
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
    glRotatef(360 * sun_tick, 0, 1, 0);
    sun_texture.bind();
    sun.draw();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    // Render Earth
    // TODO: You need to setup earth's model matrix here
    glPushMatrix();
    glRotatef(360 * earth_year_tick, 0, 1, 0);
    glTranslatef(3, 0, 0);
    glPushMatrix();
    glRotatef(360 * -earth_year_tick, 0, 1, 0);
    glRotatef(-23.5, 0, 0, 1);
    glRotatef(360 * earth_day_tick, 0, 1, 0);
    // End
    earth_texture.bind();
    earth.draw();
    // Render Moon
    // TODO: You need to setup moon's model matrix here
    glPopMatrix();
    glRotatef(360 * moon_tick, 0, 1, 0);
    glTranslatef(0.35f, 0, 0);
    // End
    moon_texture.bind();
    moon.draw();
    // TODO: Maybe you need to put some glPopMatrix here depends on your implementation.
    glPopMatrix();
    // Some platform need explicit glFlush
    glFlush();
    glfwSwapBuffers(window);
  }

  return 0;
}
