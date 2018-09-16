/*
 * main.cpp
 *
 *  Created on: Sep 15, 2018
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
	window.setSize(500,500);
	window.setTitle("YAGL Input Demo");

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(1);
		gl::clearScreen();

		std::vector<char>list=window.keys;

		if(list.size()>0){
			for(unsigned int i=0;i<list.size();i++){
				printf("%c ",list[i]);
			}
			printf("\n");
		}

		window.clearInputs();
		window.unbind();
	}

	gl::end();

	return 0;
}
