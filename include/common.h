#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifdef _WIN32
	#include <windows.h>
#endif

#define FALSE 0
#define TRUE 1

#define Q_ERROR -1
#define Q_SUCCESS 0

typedef int QSTATUS;
typedef char* SHADER_CODE;

/*
	Allocate block of memory using generic OS memory allocation
*/
QSTATUS QMemAlloc(void** data, size_t size);

/*
	Free block of memory allocated by QMemAlloc
*/
QSTATUS QMemFree(void* src);

/*
	Handle a fatal error
*/
void QFatalError(char* errorLog);

/*
	Handle an OpenGL error
*/
GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 