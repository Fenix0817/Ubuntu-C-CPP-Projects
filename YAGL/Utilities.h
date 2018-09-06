/*
 * Utilities.h
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Window.h"

namespace gl {

namespace Type {

enum type_enum {
	Byte,
	UnsignedByte,
	Short,
	UnsignedShort,
	Int,
	UnsignedInt,
	HalfFloat,
	Float,
	Double,
	Fixed
};

GLuint type_enum_to_int(type_enum te);

size_t sizeOfType(type_enum te);

}

void defaultViewport(Window w);
void setClearColor(float r,float g,float b);
void setClearColor(float gray);
void clearScreen();
float time();

const GLubyte* version();
const GLubyte* vendor();
const GLubyte* renderer();
GLuint majorVersion();
GLuint minorVersion();

} /* namespace gl */

#endif /* UTILITIES_H_ */
