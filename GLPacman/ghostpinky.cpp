/*
 * ghostpinky.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#include "ghostpinky.h"

ghost_pinky::ghost_pinky(level_ptr l) : ghost(l,"pinky") {
	// TODO Auto-generated constructor stub
	enterTime=ENTER_TIME_PINKY;
}

ghost_pinky::~ghost_pinky() {
	// TODO Auto-generated destructor stub
}

vec3 ghost_pinky::getColor(){
	return {1,0,1};
}

vec2 ghost_pinky::getTarget(player*pacman,ghost*blinky){
	return {pacman->gx+4*get_x(pacman->dir),pacman->gy+4*get_y(pacman->dir)};
}

int ghost_pinky::getEnterTime(){
	return ENTER_TIME_PINKY;
}
