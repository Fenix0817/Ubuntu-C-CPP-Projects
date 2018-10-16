/*
 * Shader.h
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#ifndef SHADER_H_
#define SHADER_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>

#include "Utilities.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::string;

namespace gl {

namespace ShaderType {

	enum shader_type_enum {
		Vertex,
		Fragment,
		Geometry
	};

	int shader_type_enum_to_int(shader_type_enum ste);
	const char* shader_type_enum_to_str(shader_type_enum ste);

}

class Shader {
public:
	Shader();
	virtual ~Shader();

	GLuint id=-1;

	bool isCreated();

	void create();
	void attach(const char*code,ShaderType::shader_type_enum type);
	void attachFile(const char*filename,ShaderType::shader_type_enum type);
	void link();

	GLuint getUniformLocation(string param);
	void setFloat(string param,float f);
	void setVec2(string param,float x,float y);
	void setVec3(string param,float x,float y,float z);
	void setVec4(string param,float x,float y,float z,float w);
	void setVec2(string param,glm::vec2 v);
	void setVec3(string param,glm::vec3 v);
	void setVec4(string param,glm::vec4 v);
	void setMat2(string param,glm::mat2 m);
	void setMat3(string param,glm::mat3 m);
	void setMat4(string param,glm::mat4 m);

	void setInt(string param,int i);

	void bind();
	void unbind();

	void del();

};

} /* namespace gl */

#endif /* SHADER_H_ */
