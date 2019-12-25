#include "include/window.h"

#define VIEWPORT_WIDTH 640
#define VIEWPORT_HEIGHT 480

GLFWwindow *setupWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "game", NULL, NULL);

  if (window == NULL) {
    printf("Failed to create window\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    printf("Error: %s\n", glewGetErrorString(glewError));
    return NULL;
  }

  glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  return window;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
