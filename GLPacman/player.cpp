/*
 * player.cpp
 *
 *  Created on: Dec 20, 2018
 *      Author: jack
 */

#include "player.h"

player::player(level_ptr l) : entity(l) {
	gx=lvl->PLAYER_X;
	gy=lvl->PLAYER_Y;
	speed=PLAYER_SPEED;
}

player::~player() {
	// TODO Auto-generated destructor stub
}

void player::render(){
	startRender();
	shd->setVec3("color",1,1,0);
	renderSquare();
}

void player::update(){
	if(canMoveInDir(nextDir)&&offx==0&&offy==0){
		dir=nextDir;
	}
	moveInDir();
	resetOff();
}

