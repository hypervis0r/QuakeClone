#include "textures.h"

QSTATUS set_texture_parameters(GLint wrap_mode, GLfloat* border_color, GLint min_filter_mode, GLint mag_filter_mode)
{
	/*
		Set texture wrap mode
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);

	/*
		If texture map mode is set to GL_CLAMP_TO_BORDER, set border color
	*/
	if (border_color != NULL)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

	/*
		Set texture filter mode
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_mode);
	glGetError();

	return Q_SUCCESS;
}

QSTATUS generate_texture(const char* texture_path, GLuint *texture_id)
{
	GLuint temp_texture_id = 0;
	int width = 0; 
	int height = 0;
	int nrChannels = 0;

	glGenTextures(1, &temp_texture_id);
	glBindTexture(GL_TEXTURE_2D, temp_texture_id);

	set_texture_parameters(GL_REPEAT, NULL, GL_LINEAR, GL_LINEAR);

	stbi_set_flip_vertically_on_load(TRUE); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
	if (!data)
	{
		QFatalError("Failed to load texture");
		return Q_ERROR;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	stbi_image_free(data);

	*texture_id = temp_texture_id;

	return Q_SUCCESS;
}