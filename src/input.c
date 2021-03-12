#include "input.h"

static unsigned char wireframe;

void process_keyboard_input(GLFWwindow* window)
{
	/*
		If key is escape, close the window
	*/
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);

	/*
		If key is F1, toggle wireframe
	*/
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, (wireframe = 1 - wireframe) ? GL_LINE : GL_FILL);
}