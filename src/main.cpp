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
  // Set up Vertices and Indices for two triangles to create one cube //////////
  float vertices[] = {
      0.5f,  0.5f,  0.0f, // Top right
      0.5f,  -0.5f, 0.0f, // Bottom right
      -0.5f, -0.5f, 0.0f, // Bottom left
      -0.5f, 0.5f,  0.0f  // Top left
  };

  unsigned int indices[] = {
      // Note that we start from 0!
      0, 1, 3, // First triangle
      1, 2, 3  // Second triangle
  };
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Set up Buffers and configure vertex attributes ////////////////////////////
  unsigned int VAO = createVertexArray();
  unsigned int VBO = createVertexBuffer();
  unsigned int EBO = createIndexBuffer();

  setVertexBuffer(vertices, sizeof(vertices));
  setIndexBuffer(indices, sizeof(indices));

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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
    // Seeing as we only have a single VAO
    // there's no need to bind it every time,
    // but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO);

    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // No need to unbind it every time

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
