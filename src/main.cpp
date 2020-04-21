#include "include/main.h"

int main(int argc, char *argv[]) {

  GLFWwindow *window = setupWindow();

  //////////////////////////////////////////////////////////////////////////////
  // Load our shaders and shader program ///////////////////////////////////////
  // (Paths are relative from "game.out" to "shaders") /////////////////////////
  // Path: "src/shaders/basic.xx.glsl" - Command: ./build/game.out /////////////
  // Path: "../src/shaders/basic.xx.glsl" - Command: ./game.out ////////////////

  unsigned int vertexShader = loadVertexShader("src/shaders/basic.vs.glsl");
  unsigned int fragmentShader = loadFragmentShader("src/shaders/basic.fs.glsl");
  unsigned int shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Two triangles next to each other using two VAOs and VBOs //////////////////
  // 1.
  float firstTriangle[] = {
    -0.9f, -0.5f, 0.0f,  // left
    -0.0f, -0.5f, 0.0f,  // right
    -0.45f, 0.5f, 0.0f,  // top
  };

  unsigned int VAO1 = genAndBindVAO();
  unsigned int VBO1 = genAndBindVBO();
  setVBOData(firstTriangle, sizeof(firstTriangle));
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 2.
  float secondTriangle[] = {
    0.0f, -0.5f, 0.0f,  // left
    0.9f, -0.5f, 0.0f,  // right
    0.45f, 0.5f, 0.0f   // top
  };

  unsigned int VAO2 = genAndBindVAO();
  unsigned int VBO2 = genAndBindVBO();
  setVBOData(secondTriangle, sizeof(secondTriangle));
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  //////////////////////////////////////////////////////////////////////////////

  while (!glfwWindowShouldClose(window)) {

    // Input
    processInput(window);

    // Render
    glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // GLFW: Swap buffers and poll IO events
    // (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO1);

  glDeleteVertexArrays(1, &VAO2);
  glDeleteBuffers(1, &VBO2);

  glfwTerminate();

  return 0;
}
