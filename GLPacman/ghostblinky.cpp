/*
 * ghostblinky.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#include "ghostblinky.h"

ghost_blinky::ghost_blinky(level_ptr l) : ghost(l,"blinky") {
	// TODO Auto-generated constructor stub
	enterTime=ENTER_TIME_BLINKY;
}

ghost_blinky::~ghost_blinky() {
	// TODO Auto-generated destructor stub
}

vec3 ghost_blinky::getColor(){
	return {1,0,0};
}
vec2 ghost_blinky::getTarget(player*pacman,ghost*blinky){
	return {pacman->gx,pacman->gy};
}

int ghost_blinky::getEnterTime(){
	return ENTER_TIME_BLINKY;
}

