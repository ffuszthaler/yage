#include "include/main.h"

int main(int argc, char *argv[]) {

  GLFWwindow *window = setupWindow();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render here

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}
