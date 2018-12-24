/*
 * main.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */


#include "Box.h"
#include "Window.h"
#include "Utils.h"
#include "Shader.h"
#include "Utilities.h"
#include "Scene.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(){
	gl::init();

	gl::Window win;
	win.create();
	win.setSize(1000,1000);
	win.setTitle("YAGL");
	win.bind();

	Scene scene;
	scene.init();

	Rect rect;
	rect.init(0,2,0,  -4,0,0,  0,0,-4);

//	gl::Texture tex=gl::createTexture(win.width,win.height,nullptr);

	gl::Framebuffer fbo[2];
	gl::Texture tex[2];
	for(int i=0;i<2;i++){
		fbo[i].create();
		fbo[i].bind();

		unsigned int rbo;
		glGenRenderbuffers(1,&rbo);
		glBindRenderbuffer(GL_RENDERBUFFER,rbo);
		glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,win.width,win.height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);

//		gl::Texture tex=gl::loadTexture("../YAGLPathtracing/Results/01-01.png");
		tex[i].setTarget(gl::TextureTarget::Tex2D);
		tex[i].create();
		tex[i].bind();
		tex[i].setParam(gl::TextureParamName::WrapS,gl::TextureParamValue::ClampToBorder);
		tex[i].setParam(gl::TextureParamName::WrapT,gl::TextureParamValue::ClampToBorder);
		tex[i].setParam(gl::TextureParamName::MinFilter,gl::TextureParamValue::Nearest);
		tex[i].setParam(gl::TextureParamName::MagFilter,gl::TextureParamValue::Nearest);
		tex[i].setData(win.width,win.height,nullptr);
		tex[i].unbind();

		fbo[i].attach(tex[i],gl::FBOAttachment::Color0);
		if(fbo[i].complete())printf("Completed\n");
		fbo[i].unbind();

		fbo[i].bind();
		gl::setClearColor(1);
		gl::clearScreen();
		fbo[i].unbind();
	}
	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/textured.frag",gl::ShaderType::Fragment);
	attachDefaultVertexShader(shader);
	shader.link();

	Rect rect1;
	rect1.init(-2,0,2,  4,0,0,  0,4,0);

	Rect rect2;
	rect2.init(-2,0,-2, 4,0,0,  0,4,0);

//	glDisable(GL_CULL_FACE);
//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	Camera camera;
	camera.camPos=glm::vec3(10,5,10);
	camera.camDir=glm::vec3(1,0,0);

	camera.forwardSpeed=0.5;
	camera.sideSpeed   =0.5;
	camera.backSpeed   =0.5;

	win.unbind();

	while(win.isOpen()){
		win.bind();

		gl::setClearColor(1,1,1);
		gl::clearScreen();
		gl::setDepth(true);
		gl::defaultViewport(win);

		camera.fovy=80;
		if(win.isKeyDown('F'))camera.fovy=20;
		camera.windowW=win.width;
		camera.windowH=win.height;

		glm::vec2 mouse=win.getMouse();
		camera.updateDirection(mouse);
		if(mouse.x<0||mouse.y<0||mouse.x>win.width||mouse.y>win.height)
				glfwSetCursorPos(win.ptr,win.width/2,win.height/2);
		mouse=win.getMouse();
		camera.mouse=mouse;

		if(win.isKeyDown('W'))camera.moveForward();
		if(win.isKeyDown('S'))camera.moveBack();
		if(win.isKeyDown('A'))camera.moveLeft();
		if(win.isKeyDown('D'))camera.moveRight();

		if(win.isKeyDown(' '))camera.camPos.y+=0.5;
		if(win.isKeyDown(GLFW_KEY_LEFT_SHIFT))camera.camPos.y-=0.5;
		if(win.isKeyDown(GLFW_KEY_ESCAPE)||win.isKeyDown('/'))win.close();

		glm::vec3 camPos=camera.camPos;
		glm::vec3 camDir=camera.camDir;

		fbo[0].bind();
		gl::setClearColor(1,1,1);
		gl::clearScreen();
		gl::setDepth(true);
		gl::defaultViewport(win);
//		camera.camPos=glm::vec3(-2+4/2,0+4/2,-2+0/2);
		camera.camPos=rect2.intersect(camPos,camDir);
//		camera.camDir=glm::vec3(0,0,1);
		scene.render( camera );
		camera.camPos=camPos;
		camera.camDir=camDir;
		fbo[0].unbind();




		gl::setClearColor(1,1,1);
		gl::clearScreen();
		gl::setDepth(true);
		gl::defaultViewport(win);

		scene.render(camera);

		shader.bind();

		shader.setInt("tex",0);
		tex[0].bindToUnit(0);

		shader.setFloat("uvScale",1);

//		glm::mat4 mvp=glm::perspective(glm::radians(80.0f), 1.0f,  0.01f,1000.0f)
//					 *glm::lookAt(camPos,glm::vec3(0,0,0),glm::vec3(0,1,0));
		shader.setMat4("MVP",camera.getPerspectiveViewMatrix());
		rect1.render();
		rect2.render();
		shader.unbind();

		win.unbind();
	}

	gl::end();
	return 0;
}

