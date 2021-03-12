#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "common.h"

/*
	Load shader code from file into memory
*/
QSTATUS load_shader(const char* shader_path, SHADER_CODE* shader, size_t* shader_buf_size);

/*
	Compile shader object from loaded shader code
*/
QSTATUS compile_shader(GLenum shaderType, SHADER_CODE shader, GLuint* shader_id);

/*
	Link shader program using array of shader ids
*/
QSTATUS link_shaders(GLuint* program_id, const GLuint* shader_array, size_t shader_count);

/*
	Generate a shader program from a fragment shader and a vertex shader
*/
QSTATUS generate_shader_program(GLuint* program_id, const char* vertex_path, const char* fragment_path);