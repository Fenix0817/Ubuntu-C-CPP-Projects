/*
 * Utilities.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "Utilities.h"

namespace gl {

namespace Type {

GLuint type_enum_to_int(type_enum te){
	if(te==Byte)return GL_BYTE;
	if(te==UnsignedByte)return GL_UNSIGNED_BYTE;
	if(te==Short)return GL_SHORT;
	if(te==UnsignedShort)return GL_UNSIGNED_SHORT;
	if(te==Int)return GL_INT;
	if(te==UnsignedInt)return GL_UNSIGNED_INT;
	if(te==HalfFloat)return GL_HALF_FLOAT;
	if(te==Float)return GL_FLOAT;
	if(te==Double)return GL_DOUBLE;
	if(te==Fixed)return GL_FIXED;
	return 0;
}

size_t sizeOfType(type_enum te){
	if(te==Short)return sizeof(short);
	if(te==UnsignedShort)return sizeof(unsigned short);
	if(te==Int)return sizeof(int);
	if(te==UnsignedInt)return sizeof(unsigned int);
	if(te==Float)return sizeof(float);
	if(te==Double)return sizeof(double);
	return 0;
}

}

void defaultViewport(Window w){
	glViewport(0,0,w.width,w.height);
}

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
