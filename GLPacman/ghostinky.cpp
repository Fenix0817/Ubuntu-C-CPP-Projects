/*
 * ghostinky.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#include "ghostinky.h"

ghost_inky::ghost_inky(level_ptr l) : ghost(l,"inky") {
	// TODO Auto-generated constructor stub
	enterTime=ENTER_TIME_INKY;
}

ghost_inky::~ghost_inky() {
	// TODO Auto-generated destructor stub
}

int ghost_inky::getEnterTime(){
	return ENTER_TIME_INKY;
}

vec2 ghost_inky::getTarget(player*pacman,ghost*blinky){
	int px=pacman->gx+2*get_x(pacman->dir);
	int py=pacman->gy+2*get_y(pacman->dir);
	int bx=blinky->gx;
	int by=blinky->gy;
	int dx=px-bx;
	int dy=py-by;
	return {bx+2*dx,by+2*dy};
}

vec3 ghost_inky::getColor(){
	return {0,1,1};
}
