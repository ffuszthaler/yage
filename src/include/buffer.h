#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

unsigned int createVertexArray();

unsigned int createVertexBuffer();

unsigned int createIndexBuffer();

void setVertexBuffer(float vertices[], size_t verticesSize);

void setIndexBuffer(unsigned int indices[], size_t indicesSize);

#endif
