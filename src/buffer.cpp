#include "include/buffer.h"

unsigned int VBO, VAO, EBO;

unsigned int genAndBindVAO() {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  return VAO;
}

unsigned int genAndBindVBO() {
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  return VBO;
}

unsigned int genAndBindEBO() {
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  return EBO;
}

void setVBOData(float vertices[], size_t verticesSize) {
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
}

void setEBOData(unsigned int indices[], size_t indicesSize) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices,
               GL_STATIC_DRAW);
}
