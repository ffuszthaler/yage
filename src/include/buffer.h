#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

unsigned int genAndBindVAO();

unsigned int genAndBindVBO();

unsigned int genAndBindEBO();

void setVBOData(float vertices[], size_t verticesSize);

void setEBOData(unsigned int indices[], size_t indicesSize);

#endif
