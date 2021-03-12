#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stb/stb_image.h>

#include "common.h"

/*
	Sets texture parameters
*/
QSTATUS set_texture_parameters(GLint wrap_mode, GLfloat* border_color, GLint min_filter_mode, GLint mag_filter_mode);

/*
	Generate an OpenGL texture from image path
*/
QSTATUS generate_texture(const char* texture_path, GLuint* texture_id);