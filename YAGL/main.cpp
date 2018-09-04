/*
 * main.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */


#include "Window.h"
#include "Shader.h"
#include "Utilities.h"
#include <stdio.h>
#include <math.h>

int main(){

	gl::init();
	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Demo");
	window.setSize(500,500);

	window.bind();

	printf("Major version ..... %i\n",gl::majorVersion());
	printf("Minor version ..... %i\n",gl::minorVersion());
	printf("Version ........... %s\n",gl::version());
	printf("Vendor ............ %s\n",gl::vendor());
	printf("Renderer .......... %s\n",gl::renderer());

	const char*vertCode="#version 450 core\nSYNTAX ERROR\nVERTEX";
	const char*fragCode="#version 450 core\nSYNTAX ERROR\nFRAGMENT";

	gl::Shader shader;
	shader.create();
	shader.attach(vertCode, gl::ShaderType::Vertex);
	shader.attach(fragCode, gl::ShaderType::Fragment);
	shader.link();

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(0.5+0.5*cos(gl::time()));
		gl::clearScreen();

		window.unbind();
	}

	gl::end();

	return 0;
}
