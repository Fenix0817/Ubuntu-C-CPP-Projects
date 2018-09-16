/*
 * Window.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "Window.h"

namespace glutils {

template<class C, class T>
auto contains(const C& v, const T& x)
-> decltype(end(v), true)
{
    return end(v) != std::find(begin(v), end(v), x);
}

}

namespace gl {

void YAGL_keypress(GLFWwindow*glfwPtr,int key,int scancode,int actions,int mods){
	Window*obj=(Window*)glfwGetWindowUserPointer(glfwPtr);
	char charKey=(char)key;
	if(actions==GLFW_PRESS){
		obj->keys.push_back(charKey);
		obj->justPressed.push_back(charKey);
	}else if(actions==GLFW_RELEASE){
		for(unsigned int i=0;i<obj->keys.size();i++){
			if(obj->keys[i]==charKey){
				obj->keys.erase(obj->keys.begin()+i);
			}
		}
		obj->justReleased.push_back(charKey);
	}
}

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

void doit(GLFWwindow*ptr,int a,int b,int c,int d){

}

void Window::create(){
	width=100;
	height=100;
	ptr=glfwCreateWindow(100,100,"Default Title", nullptr, nullptr);
	glfwSetWindowUserPointer(ptr,this);
	glfwSetKeyCallback(ptr,YAGL_keypress);
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
bool Window::isKeyDown(char c){
	return glutils::contains(keys,c);
}
bool Window::wasJustPressed(char c){
	return glutils::contains(justPressed,c);
}
bool Window::wasJustReleased(char c){
	return glutils::contains(justReleased,c);
}

void Window::clearInputs(){
	justPressed.clear();
	justReleased.clear();
}

void Window::updateSize(){
	glfwGetWindowSize(ptr,&width,&height);
}

void Window::close(){
	glfwSetWindowShouldClose(ptr,true);
}

} /* namespace gl */
