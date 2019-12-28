#include "include/buffer.h"

unsigned int VBO, VAO, EBO;

unsigned int createVertexArray() {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  return VAO;
}

unsigned int createVertexBuffer() {
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  return VBO;
}

unsigned int createIndexBuffer() {
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  return EBO;
}

void setVertexBuffer(float vertices[], size_t verticesSize) {
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
}

void setIndexBuffer(unsigned int indices[], size_t indicesSize) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices,
               GL_STATIC_DRAW);
}
