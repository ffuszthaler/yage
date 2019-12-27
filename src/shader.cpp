#include "include/shader.h"

int success;
char infoLog[512];

unsigned int loadVertexShader(const char *vShaderSource) {

  FILE *file;

  file = fopen(vShaderSource, "rb");
  if (file == nullptr) {
    std::cout << "ERROR::SHADER::VERTEX::NOT_FOUND\n"
              << vShaderSource << std::endl;
  }

  std::string content;
  fseek(file, 0, SEEK_END);
  size_t filesize = ftell(file);
  rewind(file);
  content.resize(filesize);

  fread(&content[0], 1, filesize, file);
  fclose(file);

  std::cout << "LOAD::SHADER::VERTEX - " << vShaderSource << std::endl << content << std::endl;

  const char *vertexShaderSource = content.c_str();

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

  return vertexShader;
}

unsigned int loadFragmentShader(const char *fShaderSource) {
  std::string content;
  std::ifstream fileStream(fShaderSource, std::ios::in);

  if (!fileStream.is_open()) {
    std::cerr << "ERROR::SHADER::VERTEX::NOT_FOUND\n"
              << fShaderSource << std::endl;
  }

  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();

  std::cout << "LOAD::SHADER::FRAGMENT - " << fShaderSource << std::endl << content << std::endl;

  const char *fragmentShaderSource = content.c_str();

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

  return fragmentShader;
}

unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
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

  return shaderProgram;
}
