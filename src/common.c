#include "common.h"

QSTATUS QMemAlloc(void** src, size_t size)
{
	void* data = NULL;

#ifdef _WIN32
	data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
#else
	data = malloc(size);
#endif

	if (data == NULL)
		return Q_ERROR;

	*src = data;

	return Q_SUCCESS;
}

QSTATUS QMemFree(void* src)
{
#ifdef _WIN32
	HeapFree(GetProcessHeap(), 0, src);
#else
	free(src);
#endif

	return Q_SUCCESS;
}

void QFatalError(char* errorLog)
{
#ifdef _DEBUG
	fprintf(stderr, "FATAL ERROR: %s\n", errorLog);
#else
	MessageBoxA(NULL, errorLog, "FATAL ERROR", MB_OK | MB_SYSTEMMODAL);
#endif

	exit(-1);
}

GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		char* error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:					error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:					error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:				error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:					error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:				error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:					error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:	error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		default:                                error = "UNKNOWN_ERROR";
		}
		fprintf(stderr, "ERROR: %s | %s (Line %d)\n", error, file, line);
	}
	return errorCode;
}