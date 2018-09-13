/*
 * Window.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "Window.h"

namespace gl {

void init(){
	glfwInit();
}
void end(){
	glfwTerminate();
}

Window::Window() {
	boundOnce=false;
}

Window::~Window() {
	// TODO Auto-generated destructor stub
}

void Window::setMajorVersion(int i){
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,i);
}
void Window::setMinorVersion(int i){
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,i);
}

void Window::create(){
	width=100;
	height=100;
	ptr=glfwCreateWindow(100,100,"Default Title", nullptr, nullptr);
}
void Window::setTitle(const char*title){
	glfwSetWindowTitle(ptr, title);
}
void Window::setSize(int w,int h){
	width=w;
	height=h;
	glfwSetWindowSize(ptr, w, h);
}

glm::vec2 Window::getMouse(){
	double x,y;
	glfwGetCursorPos(ptr,&x,&y);
	return glm::vec2(x,height-y);
}

void Window::bind(){
	glfwMakeContextCurrent(ptr);
	if(!boundOnce){
		boundOnce=true;
		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
			printf("GLAD cannot load\n");
			exit(EXIT_FAILURE);
		}
	}
}
void Window::unbind(){
	glfwSwapBuffers(ptr);
	glfwPollEvents();
}

bool Window::isOpen(){
	return !glfwWindowShouldClose(ptr);
}


} /* namespace gl */
