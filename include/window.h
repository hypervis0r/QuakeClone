#pragma once

#include <math.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "common.h"
#include "input.h"
#include "graphics.h"
#include "shaders.h"
#include "textures.h"

/*
	This callback is called everytime the window is resized, so our viewport will remain constant
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/*
	Our graphics window loop
*/
void render(GLFWwindow* window);