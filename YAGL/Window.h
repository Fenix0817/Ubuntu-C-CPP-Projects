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

#include <vector>
#include <algorithm>

namespace glutils {

template<class C, class T>
auto contains(const C& v, const T& x)
-> decltype(end(v), true);

}

namespace gl {

void init();
void end();

void YAGL_keypress(GLFWwindow*glfwPtr,int key,int scancode,int actions,int mods);
void YAGL_mouseclick(GLFWwindow*glfwPtr,int button,int action,int mods);

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

	std::vector<char> keys;
	std::vector<char> justPressed;
	std::vector<char> justReleased;

	bool mouseLeftJustPressed=false;
	bool mouseLeftJustReleased=false;
	bool mouseRightJustPressed=false;
	bool mouseRightJustReleased=false;

	bool mouseLeftPressed=false;
	bool mouseRightPressed=false;

	bool isKeyDown(char c);
	bool wasJustPressed(char c);
	bool wasJustReleased(char c);

	void clearInputs();
	void updateSize();

	void bind();
	void unbind();

	void close();

	bool isOpen();
};

} /* namespace gl */

#endif /* WINDOW_H_ */
