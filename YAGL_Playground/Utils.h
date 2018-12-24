/*
 * Utils.h
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#ifndef UTILS_H_
#define UTILS_H_


#include "Shader.h"

inline void attachDefaultVertexShader(gl::Shader s){
	s.attachFile("Shaders/default_vertex.vert",gl::ShaderType::Vertex);
}


#endif /* UTILS_H_ */
