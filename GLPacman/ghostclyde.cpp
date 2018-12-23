/*
 * ghostclyde.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: jack
 */

#include "ghostclyde.h"

ghost_clyde::ghost_clyde(level_ptr l) : ghost(l,"clyde") {
	// TODO Auto-generated constructor stub
	enterTime=ENTER_TIME_CLYDE;
}

ghost_clyde::~ghost_clyde() {
	// TODO Auto-generated destructor stub
}

int ghost_clyde::getEnterTime(){
	return ENTER_TIME_CLYDE;
}

vec2 ghost_clyde::getTarget(player*pacman,ghost*blinky){
	float px=pacman->gx;
	float py=pacman->gy;
	float x=gx;
	float y=gy;
	float d=sqrt( (x-px)*(x-px) + (y-py)*(y-py)  );
	if(d>8)return {px,py};
	return {0,lvl->GRID_H};
}
vec3 ghost_clyde::getColor(){
	return {1,0.4,0};
}

