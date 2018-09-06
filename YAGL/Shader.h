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

namespace gl {

namespace ShaderType {

	enum shader_type_enum {
		Vertex,
		Fragment
	};

	int shader_type_enum_to_int(shader_type_enum ste);
	const char* shader_type_enum_to_str(shader_type_enum ste);

}

class Shader {
public:
	Shader();
	virtual ~Shader();

	GLuint id;

	void create();
	void attach(const char*code,ShaderType::shader_type_enum type);
	void link();

	void bind();
	void unbind();

};

} /* namespace gl */

#endif /* SHADER_H_ */
