#include "include/main.h"

int main(int argc, char *argv[]) {

  GLFWwindow *window = setupWindow();

  //////////////////////////////////////////////////////////////////////////////
  // Load our shaders and shader program ///////////////////////////////////////
  unsigned int vertexShader = loadVertexShader("src/shaders/basic.vs.glsl");
  unsigned int fragmentShader = loadFragmentShader("src/shaders/basic.fs.glsl");
  unsigned int shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Two triangles create one cube using one VAO, VBO and EBO //////////////////
  float vertices[] = {
    0.5f,   0.5f, 0.0f, // Top right
    0.5f,  -0.5f, 0.0f, // Bottom right
    -0.5f, -0.5f, 0.0f, // Bottom left
    -0.5f,  0.5f, 0.0f  // Top left
  };

  unsigned int indices[] = {
    // Note that we start from 0!
    0, 1, 3, // First triangle
    1, 2, 3  // Second triangle
  };

  unsigned int VAO = genAndBindVAO();

  unsigned int VBO = genAndBindVBO();
  setVBOData(vertices, sizeof(vertices));

  unsigned int EBO = genAndBindEBO();
  setEBOData(indices, sizeof(indices));

  // Location in layout: 0, POSITION (3 float values)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0); // We can unbind the VAO so it can't be modified by other VAOs
  //////////////////////////////////////////////////////////////////////////////

  while (!glfwWindowShouldClose(window)) {

    // Input
    processInput(window);

    // Render
    glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // GLFW: Swap buffers and poll IO events
    // (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // De-allocate all resources
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();

  return 0;
}
