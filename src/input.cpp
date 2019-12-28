#include "include/input.h"

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  // Polygon vertices that are marked as the start of a boundary edge
  // are drawn as points.
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  }

  // Boundary edges of the polygon are drawn as line segments.
  // (Wireframe)
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  // The interior of the polygon is filled.
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
