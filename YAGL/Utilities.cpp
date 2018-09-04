/*
 * Utilities.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "Utilities.h"

namespace gl {

void setClearColor(float r,float g,float b){
	glClearColor(r,g,b,1);
}

void setClearColor(float gray){
	glClearColor(gray,gray,gray,1);
}

void clearScreen(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

float time(){
	return glfwGetTime();
}

const GLubyte* version(){
	return glGetString(GL_VERSION);
}

const GLubyte* vendor(){
	return glGetString(GL_VENDOR);
}

const GLubyte* renderer(){
	return glGetString(GL_RENDERER);
}

GLuint majorVersion(){
	int i;
	glGetIntegerv(GL_MAJOR_VERSION,&i);
	return i;
}

GLuint minorVersion(){
	int i;
	glGetIntegerv(GL_MINOR_VERSION,&i);
	return i;
}

} /* namespace gl */
