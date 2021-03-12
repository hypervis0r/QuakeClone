#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include "common.h"

/*
	Generate and bind a Vertex Buffer Object to the GL_ARRAY_BUFFER
*/
QSTATUS generate_vbo(GLuint* VBO);

/*
	Generate and bind a Vertex Array Object
*/
QSTATUS generate_vao(GLuint* VAO);

/*
	Set and enable the Vertex Attrib Array
*/
QSTATUS set_vertex_attrib_pointer(void);

/*
	Load a given array of vertices into a VAO/VBO
*/
QSTATUS load_vertex(
	const GLfloat* vertex,
	GLsizeiptr vertex_size,
	const GLuint* index,
	GLsizeiptr index_size,
	GLuint* VBO,
	GLuint* EBO,
	GLuint* VAO
);