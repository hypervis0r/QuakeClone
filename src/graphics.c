#include "graphics.h"

QSTATUS generate_vbo(GLuint *VBO)
{
	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);

	return Q_SUCCESS;
}

QSTATUS generate_vao(GLuint* VAO)
{
	glGenVertexArrays(1, VAO);
	glBindVertexArray(*VAO);

	return Q_SUCCESS;
}

QSTATUS set_vertex_attrib_pointer(void)
{
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// color attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	return Q_SUCCESS;
}

QSTATUS load_vertex(
	const GLfloat* vertex, 
	GLsizeiptr vertex_size, 
	const GLuint *index, 
	GLsizeiptr index_size, 
	GLuint *VBO, 
	GLuint *EBO, 
	GLuint *VAO)
{
	GLuint temp_vbo = 0;
	GLuint temp_ebo = 0;
	GLuint temp_vao = 0;

	if (vertex == NULL ||
		index == NULL ||
		VBO == NULL ||
		EBO == NULL ||
		VAO == NULL)
			return Q_ERROR;
	
	glGenVertexArrays(1, &temp_vao);
	glGenBuffers(1, &temp_vbo);
	glGenBuffers(1, &temp_ebo);

	glBindVertexArray(temp_vao);

	glBindBuffer(GL_ARRAY_BUFFER, temp_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, index, GL_STATIC_DRAW);

	set_vertex_attrib_pointer();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	*VBO = temp_vbo;
	*VAO = temp_vao;
	*EBO = temp_ebo;

	return Q_SUCCESS;
}