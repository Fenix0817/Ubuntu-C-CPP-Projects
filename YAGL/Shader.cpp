/*
 * Shader.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "Shader.h"

namespace gl {

namespace ShaderType {

int shader_type_enum_to_int(shader_type_enum ste){
	if(ste==Vertex)return GL_VERTEX_SHADER;
	if(ste==Fragment)return GL_FRAGMENT_SHADER;
	return 0;
}


const char* shader_type_enum_to_str(shader_type_enum ste){
	if(ste==Vertex)return "Vertex";
	if(ste==Fragment)return "Fragment";
	return 0;
}

}

Shader::Shader() {
	// TODO Auto-generated constructor stub

}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}


void Shader::create(){
	id=glCreateProgram();
}
void Shader::attach(const char*code,ShaderType::shader_type_enum type){
	int s=glCreateShader(ShaderType::shader_type_enum_to_int(type));
	glShaderSource(s,1,&code,nullptr);
	glCompileShader(s);

	int success;
	char log[512];
	glGetShaderiv(s,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(s,512,nullptr,log);
		printf("%s shader error\n%s\n",ShaderType::shader_type_enum_to_str(type),log);
	}

	glAttachShader(id,s);
}
void Shader::link(){
	glLinkProgram(id);
}

void Shader::bind(){
	glUseProgram(id);
}
void Shader::unbind(){
	glUseProgram(0);
}

} /* namespace gl */
