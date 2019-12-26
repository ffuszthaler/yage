#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>

unsigned int LoadVertexShader(const char *vShaderSource);

unsigned int LoadFragmentShader(const char *fShaderSource);

unsigned int LoadShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
#endif
