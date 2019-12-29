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
  // float vertices[] = {
  //   0.5f,   0.5f, 0.0f, // Top right
  //   0.5f,  -0.5f, 0.0f, // Bottom right
  //   -0.5f, -0.5f, 0.0f, // Bottom left
  //   -0.5f,  0.5f, 0.0f  // Top left
  // };

  // unsigned int indices[] = {
  //   // Note that we start from 0!
  //   0, 1, 3, // First triangle
  //   1, 2, 3  // Second triangle
  // };

  // unsigned int VAO = createVertexArray();

  // unsigned int VBO = createVertexBuffer();
  // setVertexBuffer(vertices, sizeof(vertices));

  // unsigned int EBO = createIndexBuffer();
  // setIndexBuffer(indices, sizeof(indices));

  // // Location in layout: 0, POSITION (3 float values)
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // glEnableVertexAttribArray(0);
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Two triangles next to each other using two VAOs and VBOs //////////////////
  float firstTriangle[] = {
    -0.9f, -0.5f, 0.0f,  // left
    -0.0f, -0.5f, 0.0f,  // right
    -0.45f, 0.5f, 0.0f,  // top
  };

  float secondTriangle[] = {
    0.0f, -0.5f, 0.0f,  // left
    0.9f, -0.5f, 0.0f,  // right
    0.45f, 0.5f, 0.0f   // top
  };

  unsigned int VAO1 = createVertexArray();
  unsigned int VBO1 = createVertexBuffer();
  setVertexBuffer(firstTriangle, sizeof(firstTriangle));
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  unsigned int VAO2 = createVertexArray();
  unsigned int VBO2 = createVertexBuffer();
  setVertexBuffer(secondTriangle, sizeof(secondTriangle));
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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

    // Seeing as we only have a single VAO
    // there's no need to bind it every time,
    // but we'll do so to keep things a bit more organized
    // glBindVertexArray(VAO);

    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // No need to unbind it every time

    // GLFW: Swap buffers and poll IO events
    // (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // De-allocate all resources
  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // glDeleteBuffers(1, &EBO);

  glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO1);

  glDeleteVertexArrays(1, &VAO2);
  glDeleteBuffers(1, &VBO2);

  glfwTerminate();

  return 0;
}
