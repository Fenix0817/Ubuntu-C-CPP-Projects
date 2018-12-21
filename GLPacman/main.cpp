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
	window.setSize(500,500);
	window.bind();
	glfwSetKeyCallback(window.ptr,key_callback);

	printf("%s\n",glGetString(GL_VERSION));
	GLint maj,min;
	glGetIntegerv(GL_MAJOR_VERSION,&maj);
	glGetIntegerv(GL_MINOR_VERSION,&min);
	printf("%i.%i\n",maj,min);

	initSquare();

	level_ptr lvl=new level();
	lvl->GRID_W=28;
	lvl->GRID_H=31;
	lvl->PLAYER_X=15;
	lvl->PLAYER_Y=17;
	lvl->GHOST_X=-10000;
	lvl->GHOST_Y=-10000;
	lvl->GHOST_EXIT_X=-10000;
	lvl->GHOST_EXIT_Y=-10000;
	int tiles[lvl->GRID_H][lvl->GRID_W]=
{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
{1,4,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,4,1},
{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
{1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
{1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
{1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
{1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
{0,0,0,0,0,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0},
{1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
{0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0},
{1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
{0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0},
{1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
{1,4,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,4,1},
{1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
{1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
{1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
{1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
{1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	//C++ SUCKS AAAAAGGGHGHHHH
	int**__level__=new int*[lvl->GRID_H];
	for(int a=0;a<lvl->GRID_H;a++){
		__level__[a]=new int[lvl->GRID_W];
		for(int b=0;b<lvl->GRID_W;b++){
			__level__[a][b]=tiles[a][b];
		}
	}
	lvl->put_tiles(__level__);

	player*pacman=new player(lvl);

	window.setSize(lvl->GRID_W*30,lvl->GRID_H*30);

	square_shader uvShader("uv.frag");
	square_shader colorShader("color.frag");

	while(window.isOpen()){
		window.bind();

		gl::defaultViewport(window);
		gl::setClearColor(0,0,0);
		gl::clearScreen();

		pacman->nextDir=nextDir;
		pacman->render();
		pacman->update();

		for(int x=0;x<lvl->GRID_W;x++){
			for(int y=0;y<lvl->GRID_H;y++){
				if(lvl->tiles[x][y]==WALL){
					colorShader.render(((float)x)/lvl->GRID_W,((float)y)/lvl->GRID_H,1.0/lvl->GRID_W,1.0/lvl->GRID_H);
					colorShader.setVec3("color",0,0,1);
					renderSquare();
				}
			}
		}

		window.unbind();
	}

	deleteSquare();

	gl::end();
	return 0;
}

