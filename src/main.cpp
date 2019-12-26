#include "include/main.h"

int main(int argc, char *argv[]) {

  GLFWwindow *window = setupWindow();

  //////////////////////////////////////////////
  // Build and compile our shaders /////////////
  unsigned int vertexShader = LoadVertexShader("src/shaders/basic.vs.glsl");
  unsigned int fragmentShader = LoadFragmentShader("src/shaders/basic.fs.glsl");
  unsigned int shaderProgram = LoadShaderProgram(vertexShader, fragmentShader);

  ////////////////////////////////////////////////////////////////////////
  // Set up Vertices and Indices for to triangles to create a cube ///////
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
  ////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////
  // Set up Buffers and configure vertex attributes //////////////////////
  unsigned int VBO, VAO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &VBO);

  // Bind the Vertex Array Object first, then bind and set vertex buffer(s),
  // and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Note that this is allowed, the call to glVertexAttribPointer
  // registered VBO as the vertex attribute's bound vertex buffer object
  // so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't
  // accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally
  // don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);
  ////////////////////////////////////////////////////////////////////////

  // Uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
