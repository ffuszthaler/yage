#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>

unsigned int loadVertexShader(const char *vShaderSource);

unsigned int loadFragmentShader(const char *fShaderSource);

unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
#endif
