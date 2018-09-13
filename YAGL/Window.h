/*
 * Window.h
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

namespace gl {

void init();
void end();

class Window {
public:
	Window();
	virtual ~Window();

	GLFWwindow*ptr;

	bool boundOnce;

	int width;
	int height;

	void setMajorVersion(int i);
	void setMinorVersion(int i);

	void create();
	void setTitle(const char*title);
	void setSize(int w,int h);

	glm::vec2 getMouse();

	void bind();
	void unbind();

	bool isOpen();
};

} /* namespace gl */

#endif /* WINDOW_H_ */
