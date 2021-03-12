#include "shaders.h"

QSTATUS load_shader(const char* shader_path, SHADER_CODE* shader, size_t* shader_buf_size)
{
	QSTATUS qResult = 0;
	size_t stBytesRead = 0;
	SHADER_CODE temp = NULL;

#ifdef _WIN32
	HANDLE hFile = 0;
	LARGE_INTEGER liFileSize = { 0 };
	DWORD dwLength = 0;

	hFile = CreateFileA(
		shader_path,     /* lpFileName */
		GENERIC_READ,   /* dwDesiredAccess */
		0,              /* dwShareMode */
		0,              /* lpSecurityAttributes */
		OPEN_EXISTING,  /* dwCreationDisposition */
		FILE_ATTRIBUTE_READONLY,    /* dwFlagsAndAttributes */
		0               /* hTemplateFile */
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "[-] CreateFileA: %d\n", GetLastError());
		return Q_ERROR;
	}

	/* Get file size */
	qResult = GetFileSizeEx(hFile, &liFileSize);
	if (qResult == NULL)
	{
		CloseHandle(hFile);
		fprintf(stderr, "[-] GetFileSizeEx: %d\n", GetLastError());
		return Q_ERROR;
	}

	dwLength = liFileSize.QuadPart;

	/* Allocate Memory */
	qResult = QMemAlloc(&temp, dwLength);
	if (qResult == Q_ERROR)
	{
		CloseHandle(hFile);
		return Q_ERROR;
	}

	/* Read file into buffer */
	qResult = ReadFile(
		hFile,          /* hFile */
		temp,           /* lpBuffer */
		dwLength,       /* nNumberOfBytesToRead */
		&stBytesRead,   /* lpNumberOfBytesRead */
		0               /* lpOverlapped */
	);
	if (qResult == FALSE)
	{
		CloseHandle(hFile);
		QMemFree(temp);

		fprintf(stderr, "[-] ReadFile: %d\n", GetLastError());
		return Q_ERROR;
	}

	CloseHandle(hFile);
#else
	struct stat st = { 0 };
	int filesize = 0;
	int fd = 0;

	/* Get File Size */
	iResult = stat(cpFilePath, &st);
	if (iResult == -1)
		return Q_ERROR;

	filesize = st.st_size;

	/* Open File Descriptor */
	fd = open(cpFilePath, O_RDONLY);
	if (fd == -1)
		return Q_ERROR;

	/* Allocate buffer */
	iResult = QMemAlloc(&temp, filesize);
	if (iResult == HYPER_FAILED)
		return Q_ERROR;

	/* Read file into buffer */
	stBytesRead = read(fd, temp, filesize);
	if ((int)stBytesRead == -1)
	{
		close(fd);
		QMemFree(temp);
		return Q_ERROR;
	}

	close(fd);
#endif

	/* Set SHADER and size_t parameter */
	* shader = temp;
	*shader_buf_size = stBytesRead;

	return Q_SUCCESS;
}

QSTATUS compile_shader(GLenum shaderType, SHADER_CODE shader, GLuint* shader_id)
{
	GLuint temp_shader_id = 0;
	int success = 0;
	char infoLog[512] = { 0 };

	if (shader_id == NULL ||
		shader == NULL)
		return Q_ERROR;

	/*
		Generate the shader id
	*/
	temp_shader_id = glCreateShader(shaderType);

	/*
		Compile the shader
	*/
	glShaderSource(temp_shader_id, 1, &shader, NULL);
	glCompileShader(temp_shader_id);

	/*
		Check shader compilation
	*/
	glGetShaderiv(temp_shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(temp_shader_id, 512, NULL, infoLog);
		QFatalError(infoLog);
		return Q_ERROR;
	}

	*shader_id = temp_shader_id;

	return Q_SUCCESS;
}

QSTATUS link_shaders(GLuint* program_id, const GLuint* shader_array, size_t shader_count)
{
	GLuint temp_program_id = 0;
	GLint success = 0;
	char infoLog[512] = { 0 };

	if (program_id == NULL ||
		shader_array == NULL)
		return Q_ERROR;

	/*
		Generate program id
	*/
	temp_program_id = glCreateProgram();

	/*
		Attach all of the shaders specified
	*/
	for (size_t i = 0; i < shader_count; i++)
	{
		glAttachShader(temp_program_id, shader_array[i]);
	}

	/*
		Link the shader program
	*/
	glLinkProgram(temp_program_id);

	/*
		Check for linker errors
	*/
	glGetProgramiv(temp_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(temp_program_id, 512, NULL, infoLog);
		QFatalError(infoLog);

		return Q_ERROR;
	}

	*program_id = temp_program_id;

	return Q_SUCCESS;
}

QSTATUS generate_shader_program(GLuint* program_id, const char* vertex_path, const char* fragment_path)
{
	QSTATUS qResult = 0;
	GLuint temp_program_id = 0;

	SHADER_CODE frag_shader_code = NULL;
	SHADER_CODE vert_shader_code = NULL;
	size_t frag_shader_size = 0;
	size_t vert_shader_size = 0;
	GLuint shader_array[2] = { 0 };
	GLuint shader_array_size = 2;

	// load shaders
	qResult = load_shader(fragment_path, &frag_shader_code, &frag_shader_size);
	if (qResult != Q_SUCCESS)
		return Q_ERROR;

	qResult = load_shader(vertex_path, &vert_shader_code, &vert_shader_size);
	if (qResult != Q_SUCCESS)
		return Q_ERROR;

	// Compile shaders
	qResult = compile_shader(GL_FRAGMENT_SHADER, frag_shader_code, &shader_array[0]);
	if (qResult != Q_SUCCESS)
		return Q_ERROR;

	qResult = compile_shader(GL_VERTEX_SHADER, vert_shader_code, &shader_array[1]);
	if (qResult != Q_SUCCESS)
		return Q_ERROR;

	QMemFree(frag_shader_code);
	QMemFree(vert_shader_code);

	// Link shader program
	qResult = link_shaders(&temp_program_id, shader_array, shader_array_size);
	if (qResult != Q_SUCCESS)
	{
		glDeleteShader(shader_array[0]);
		glDeleteShader(shader_array[1]);
		return Q_ERROR;
	}

	glDeleteShader(shader_array[0]);
	glDeleteShader(shader_array[1]);

	*program_id = temp_program_id;

	return Q_SUCCESS;
}