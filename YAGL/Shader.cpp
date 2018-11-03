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
	if(ste==Geometry)return GL_GEOMETRY_SHADER;
	return 0;
}


const char* shader_type_enum_to_str(shader_type_enum ste){
	if(ste==Vertex)return "Vertex";
	if(ste==Fragment)return "Fragment";
	if(ste==Geometry)return "Geometry";
	return 0;
}

}

Shader::Shader() {
	// TODO Auto-generated constructor stub

}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

bool Shader::isCreated(){
	return id!=-1;
}

GLuint Shader::getUniformLocation(string param){
	return glGetUniformLocation(id,param.c_str());
}
void Shader::setInt(string param,int i){
#ifdef GL_SHADER_DEBUG_setInt
	printf("gl::Shader setInt %s = %i\n",param.c_str(),i);
#endif
	glUniform1i(getUniformLocation(param),i);
}
void Shader::setFloat(string param,float f){
#ifdef GL_SHADER_DEBUG_setFloat
	printf("gl::Shader setFloat %s = %f\n",param.c_str(),f);
#endif
	glUniform1f(getUniformLocation(param),f);
}
void Shader::setVec2(string param,float x,float y){
#ifdef GL_SHADER_DEBUG_setVec2
	printf("gl::Shader setVec2 %s = (%f, %f)\n",param.c_str(),x,y);
#endif
	glUniform2f(getUniformLocation(param),x,y);
}
void Shader::setVec3(string param,float x,float y,float z){
#ifdef GL_SHADER_DEBUG_setVec3
	printf("gl::Shader setVec3 %s = (%f, %f, %f)\n",param.c_str(),x,y,z);
#endif
	glUniform3f(getUniformLocation(param),x,y,z);
}
void Shader::setVec4(string param,float x,float y,float z,float w){
#ifdef GL_SHADER_DEBUG_setVec4
	printf("gl::Shader setVec4 %s = (%f, %f, %f, %f)\n",param.c_str(),x,y,z,w);
#endif
	glUniform4f(getUniformLocation(param),x,y,z,w);
}
void Shader::setVec2(string param,glm::vec2 v){
#ifdef GL_SHADER_DEBUG_setVec2
	printf("gl::Shader setVec2 %s = (%f, %f)\n",param.c_str(),v.x,v.y);
#endif
	glUniform2fv(getUniformLocation(param),1,glm::value_ptr(v));
}
void Shader::setVec3(string param,glm::vec3 v){
#ifdef GL_SHADER_DEBUG_setVec3
	printf("gl::Shader setVec3 %s = (%f, %f, %f)\n",param.c_str(),v.x,v.y,v.z);
#endif
	glUniform3fv(getUniformLocation(param),1,glm::value_ptr(v));
}
void Shader::setVec4(string param,glm::vec4 v){
#ifdef GL_SHADER_DEBUG_setVec4
	printf("gl::Shader setVec4 %s = (%f, %f, %f, %f)\n",param.c_str(),v.x,v.y,v.z,v.w);
#endif
	glUniform4fv(getUniformLocation(param),1,glm::value_ptr(v));
}
void Shader::setMat2(string param,glm::mat2 m){
#ifdef GL_SHADER_DEBUG_setMat2
	printf("gl::Shader setMat2 %s\n",param.c_str());
#endif
	glUniformMatrix2fv(getUniformLocation(param),1,GL_FALSE,glm::value_ptr(m));
}
void Shader::setMat3(string param,glm::mat3 m){
#ifdef GL_SHADER_DEBUG_setMat3
	printf("gl::Shader setMat3 %s\n",param.c_str());
#endif
	glUniformMatrix3fv(getUniformLocation(param),1,GL_FALSE,glm::value_ptr(m));
}
void Shader::setMat4(string param,glm::mat4 m){
#ifdef GL_SHADER_DEBUG_setMat4
	printf("gl::Shader setMat4 %s\n",param.c_str());
#endif
	glUniformMatrix4fv(getUniformLocation(param),1,GL_FALSE,glm::value_ptr(m));
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
void Shader::attachFile(const char*filename,ShaderType::shader_type_enum type){
	attach(gl::readFile(filename).c_str(),type);
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

void Shader::del(){
	glDeleteProgram(id);
	id=-1;
}

} /* namespace gl */
