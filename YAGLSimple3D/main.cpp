/*
 * main.cpp
 *
 *  Created on: Sep 7, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "RGBCube.h"

int main(){

	gl::init();

	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("Simple 3D");
	window.setSize(300,500);
	window.bind();
	//FIGURE OUT GIT

	printf("Major version ..... %i\n",gl::majorVersion());
	printf("Minor version ..... %i\n",gl::minorVersion());
	printf("Version ........... %s\n",gl::version());
	printf("Vendor ............ %s\n",gl::vendor());
	printf("Renderer .......... %s\n",gl::renderer());

	RGBCube rgbCube;

	rgbCube.init();

	window.unbind();

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(1);
		gl::clearScreen();
		gl::defaultViewport(window);
		gl::setDepth(true);

		glm::mat4 model=glm::rotate(gl::time(),glm::vec3(0.0f,1.0f,0.0f));
		glm::mat4 view=glm::lookAt(glm::vec3(2,-3,3),glm::vec3(0,0,0),glm::vec3(0,1,0));
		glm::mat4 perspective=glm::perspective(80.0,1.0*window.width/window.height,0.01,100.0);

		rgbCube.render(perspective,view,model);

		window.unbind();
	}

	gl::end();

	return 0;
}
