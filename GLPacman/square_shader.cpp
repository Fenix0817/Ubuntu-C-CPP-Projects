/*
 * square_shader.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#include "square_shader.h"

square_shader::square_shader(std::string fn) {
	// TODO Auto-generated constructor stub
	s.create();
	s.attachFile("shader.vert",gl::ShaderType::Vertex);
	s.attachFile(fn.c_str(),gl::ShaderType::Fragment);
	s.link();
}

square_shader::~square_shader() {
	// TODO Auto-generated destructor stub
}

void square_shader::render(float x,float y,float w,float h){
	s.bind();
	s.setVec2("pos",x,y);
	s.setVec2("size",w,h);
}

void square_shader::setVec3(std::string n,float x,float y,float z){
	s.setVec3(n,x,y,z);
}

void square_shader::setInt(std::string n,int i){
	s.setInt(n,i);
}

