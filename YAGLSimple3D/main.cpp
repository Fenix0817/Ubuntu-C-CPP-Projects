/*
 * main.cpp
 *
 *  Created on: Sep 7, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"

int main(){

	gl::init();

	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("Simple 3D");
	window.setSize(500,500);
	window.bind();

	printf("Major version ..... %i\n",gl::majorVersion());
	printf("Minor version ..... %i\n",gl::minorVersion());
	printf("Version ........... %s\n",gl::version());
	printf("Vendor ............ %s\n",gl::vendor());
	printf("Renderer .......... %s\n",gl::renderer());

	window.unbind();

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(1);
		gl::clearScreen();

		window.unbind();
	}

	gl::end();

	return 0;
}
