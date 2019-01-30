/*
 * utils.h
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <glm/glm.hpp>
#include <math.h>
#include <YAGL.h>

float max(float a,float b);
float lerp(float t,float a,float b);
float norm(float t,float a,float b);
float map(float t,float s1,float e1,float s2,float e2);

const float PI=3.14159265359;

inline const char*b2s(bool b){
	return b?"true":"false";
}

inline bool printError(){
	GLenum e=glGetError();
	switch(e){
	case GL_NO_ERROR: printf("GL_NO_ERROR\n"); return false;
	case GL_INVALID_ENUM: printf("GL_INVALID_ENUM\n"); return true;
	case GL_INVALID_VALUE: printf("GL_INVALID_VALUE\n"); return true;
	case GL_INVALID_OPERATION: printf("GL_INVALID_OPERATION\n"); return true;
	case GL_INVALID_FRAMEBUFFER_OPERATION: printf("GL_INVALID_FRAMEBUFFER_OPERATION\n"); return true;
	case GL_OUT_OF_MEMORY: printf("GL_OUT_OF_MEMORY\n"); return true;
	case GL_STACK_UNDERFLOW: printf("GL_STACK_UNDERFLOW\n"); return true;
	case GL_STACK_OVERFLOW: printf("GL_STACK_OVERFLOW\n"); return true;
	}
	return false;
}

void debugGL();

namespace glm {

//typedef glm::vec<2,int,glm::qualifier::defaultp> vec2i;

}

#endif /* UTILS_H_ */
