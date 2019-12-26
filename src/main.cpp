#include "include/main.h"

#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////
// Read external .glsl files ///////////////////////////////////////////
std::string LoadVertexShader(const char *vShaderSource) {

  FILE *file;

  file = fopen(vShaderSource, "rb");
  if (file == nullptr) {
    std::cout << "ERROR::SHADER::VERTEX::NOT_FOUND\n"
              << vShaderSource << std::endl;
    return 0;
  }

  std::string content;
  fseek(file, 0, SEEK_END);
  size_t filesize = ftell(file);
  rewind(file);
  content.resize(filesize);

  fread(&content[0], 1, filesize, file);
  fclose(file);

  std::cout << "'" << content << "'" << std::endl;
  return content;
}

std::string LoadFragmentShader(const char *fShaderSource) {
  std::string content;
  std::ifstream fileStream(fShaderSource, std::ios::in);

  if (!fileStream.is_open()) {
    std::cerr << "ERROR::SHADER::VERTEX::NOT_FOUND\n"
              << fShaderSource << std::endl;
    return "";
  }

  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  std::cout << "'" << content << "'" << std::endl;
  return content;
}
////////////////////////////////////////////////////////////////////////

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

int main(int argc, char *argv[]) {

  GLFWwindow *window = setupWindow();

  LoadVertexShader("src/shaders/basic.vs.glsl");

  LoadFragmentShader("src/shaders/basic.fs.glsl");

  //////////////////////////////////////////////
  // Build and compile our shaders /////////////
  // Vertex shader
  int success;
  char infoLog[512];

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  //////////////////////////////////////////////

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
