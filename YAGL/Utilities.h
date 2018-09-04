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

namespace gl {

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
