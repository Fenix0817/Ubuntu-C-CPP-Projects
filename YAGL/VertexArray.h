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

	GLuint id=-1;

	bool isCreated();

	void create();
	void bind();
	void unbind();

	void del();
};

} /* namespace gl */

#endif /* VERTEXARRAY_H_ */
