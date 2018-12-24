/*
 * main.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"

#include "level.h"
#include "square.h"
#include "square_shader.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "ghostblinky.h"
#include "ghostpinky.h"
#include "ghostinky.h"
#include "ghostclyde.h"

#include "level1.h"

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig){
	void*array[100];
	size_t size;

	size=backtrace(array,100);
	fprintf(stderr,"Error: signal %d, with elements %i:\n",sig,(int)size);
	backtrace_symbols_fd(array,size,STDERR_FILENO);
	exit(1);
}

Dir nextDir=DIR_NONE;

void key_callback(GLFWwindow*w,int k,int s,int a,int m){
	if(a==GLFW_PRESS){
		if(k==GLFW_KEY_A)nextDir=DIR_L;
		if(k==GLFW_KEY_D)nextDir=DIR_R;
		if(k==GLFW_KEY_W)nextDir=DIR_U;
		if(k==GLFW_KEY_S)nextDir=DIR_D;
	}
}

int main(){
	signal(SIGSEGV,handler);
	gl::init();

	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("Pacman in OpenGL");
	window.bind();
	glfwSetKeyCallback(window.ptr,key_callback);

	printf("%s\n",glGetString(GL_VERSION));
	GLint maj,min;
	glGetIntegerv(GL_MAJOR_VERSION,&maj);
	glGetIntegerv(GL_MINOR_VERSION,&min);
	printf("%i.%i\n",maj,min);

	initSquare();

	level_ptr lvl=level1_make();

	player*pacman=new player(lvl);
	ghost_blinky*blinky=new ghost_blinky(lvl);
	ghost_pinky*pinky=new ghost_pinky(lvl);
	ghost_inky*inky=new ghost_inky(lvl);
	ghost_clyde*clyde=new ghost_clyde(lvl);

	window.setSize(lvl->GRID_W*30,lvl->GRID_H*30);

	square_shader colorShader("color.frag");
	square_shader texturedShader("textured.frag");

	gl::Texture tex=gl::loadTexture("Textures/level1.png");

	while(window.isOpen()){
		window.bind();

		gl::defaultViewport(window);
		gl::setClearColor(0,0,0);
		gl::clearScreen();

		texturedShader.render(0,0,1,1);
		texturedShader.setInt("tex",0);
		tex.bindToUnit(0);
		renderSquare();

		float dx=1.0f/lvl->GRID_W;
		float dy=1.0f/lvl->GRID_H;
		for(int x=0;x<lvl->GRID_W;x++){
			for(int y=0;y<lvl->GRID_H;y++){
				if(lvl->dots[x][y]){
					colorShader.render(  (x+0.5-DOT_SIZE)*dx,(y+0.5-DOT_SIZE)*dy,2*DOT_SIZE*dx,2*DOT_SIZE*dy  );
					colorShader.setVec3("color",1,1,1);
					renderSquare();
				}
				if(lvl->power_dots[x][y]){
					colorShader.render(  (x+0.5-POWER_DOT_SIZE)*dx,(y+0.5-POWER_DOT_SIZE)*dy,2*POWER_DOT_SIZE*dx,2*POWER_DOT_SIZE*dy  );
					colorShader.setVec3("color",1,1,1);
					renderSquare();
				}
			}
		}

		blinky->render();
		blinky->update(pacman,blinky);

		pinky->render();
		pinky->update(pacman,blinky);

		inky->render();
		inky->update(pacman,blinky);

		clyde->render();
		clyde->update(pacman,blinky);

		pacman->nextDir=nextDir;
		pacman->render();
		pacman->update(blinky,pinky,inky,clyde);


		window.unbind();
	}

	deleteSquare();

	gl::end();
	return 0;
}

