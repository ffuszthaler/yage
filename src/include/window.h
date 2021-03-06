#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

GLFWwindow *setupWindow();

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

#endif
