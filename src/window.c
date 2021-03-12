#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void render(GLFWwindow* window)
{
	QSTATUS qResult = 0;
	
	const GLfloat triangle_verts[] = {
		// positions          // colors           // texture coords
		-1.f,  1.f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		-1.f,  -1.f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	     1.f, -1.f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	     1.f,  1.f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	const GLuint indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};

	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint EBO = 0;

	GLuint color_shader_program = 0;

	GLuint texture_id = 0;

	// Generate the shader program for orange
	qResult = generate_shader_program(&color_shader_program, "src/shaders/color.vert.glsl", "src/shaders/color.frag.glsl");
	if (qResult != Q_SUCCESS)
		QFatalError("Failed to generate shader program!");

	// Load vertex array into buffer
	qResult = load_vertex(triangle_verts, sizeof(triangle_verts), indices, sizeof(indices), &VBO, &EBO, &VAO);
	if (qResult != Q_SUCCESS)
		QFatalError("Failed to load vertex!");

	qResult = generate_texture("resources/yes.png", &texture_id);
	if (qResult != Q_SUCCESS)
		QFatalError("Failed to generate texture!");

	mat4 trans = { 
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	};
	glm_rotate(trans, glm_rad(90.0f), (vec3) { 0.0, 0.0, 1.0 });
	glm_scale(trans, (vec3) { 0.5, 0.5, 0.5 });
	printf("%f %f %f %f", trans[0][0], trans[0][1], trans[0][2], trans[0][3]);

	while (!glfwWindowShouldClose(window))
	{
		process_keyboard_input(window);

		glClearColor(0.1f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glUseProgram(color_shader_program);

		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(color_shader_program, "inColor");
		glUniform4f(vertexColorLocation, greenValue, 0.0f, greenValue, 1.0f);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}