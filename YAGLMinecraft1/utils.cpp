/*
 * utils.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#include "utils.h"

float max(float a,float b){
	if(a>b)return a;
	return b;
}

float lerp(float t,float a,float b){
	return (b-a)*t+a;
}
float norm(float t,float a,float b){
	return (t-a)/(b-a);
}
float map(float t,float s1,float e1,float s2,float e2){
	return lerp(norm(t,s1,e1),s2,e2);
}

void debugGL(){
	auto err=glGetError();

	std::string errStr="";
	switch(err){
	case GL_INVALID_ENUM:
		errStr="GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		errStr="GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		errStr="GL_INVALID_OPERATION";
		break;
	case GL_STACK_OVERFLOW:
		errStr="GL_STACK_OVERFLOW";
		break;
	case GL_STACK_UNDERFLOW:
		errStr="GL_STACK_UNDERFLOW";
		break;
	case GL_OUT_OF_MEMORY:
		errStr="GL_OUT_OF_MEMORY";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		errStr="GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	case GL_CONTEXT_LOST:
		errStr="GL_CONTEXT_LOST";
		break;
	case GL_TABLE_TOO_LARGE:
		errStr="GL_TABLE_TOO_LARGE";
		break;
	default:
		errStr="GL_NO_ERROR";
		break;
	}
	printf("Error: %i, error string: %s\n",err,errStr.c_str());
}
