/*
 * VertexArray.h
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace gl {

class VertexArray {
public:
	VertexArray();
	virtual ~VertexArray();

	GLuint id;

	void create();
	void bind();
	void unbind();
};

} /* namespace gl */

#endif /* VERTEXARRAY_H_ */
