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
	anim=new animator(4,  2,"pacman");
}

player::~player() {
	// TODO Auto-generated destructor stub
}

void player::render(){
	anim->render(gx,gy,offx,offy,dir,lvl->GRID_W,lvl->GRID_H);
	anim->step();
	for(bonus*b:bonuses){
		if(b->life>0){
			b->render();
		}
		printf("%i\n",b->life);
		b->life--;
	}
//	startRender();
//	shd->setVec3("color",1,1,0);
//	renderSquare();
}

bool player::hasHit(ghost*g){
	return gx==g->gx&&gy==g->gy;
}

void player::die(ghost*blinky,ghost*pinky,ghost*inky,ghost*clyde){
	gx=lvl->PLAYER_X;
	gy=lvl->PLAYER_Y;
	offx=0;
	offy=0;
	blinky->reset();
	pinky->reset();
	inky->reset();
	clyde->reset();
}

void player::update(ghost*blinky,ghost*pinky,ghost*inky,ghost*clyde){
	if(canMoveInDir(nextDir)&&offx==0&&offy==0){
		dir=nextDir;
	}
	lvl->dots[gx][gy]=false;
	if(lvl->power_dots[gx][gy]){
		lvl->power_dots[gx][gy]=false;
		bonusAmount=200;
		blinky->scare();
		pinky->scare();
		inky->scare();
		clyde->scare();
	}
	if(hasHit(blinky)){
		if(blinky->scared){
			blinky->die();
			newBonus();
		}else{
			die(blinky,pinky,inky,clyde);
		}
	}
	if(hasHit(pinky)){
		if(pinky->scared){
			pinky->die();
			newBonus();
		}else{
			die(blinky,pinky,inky,clyde);
		}
	}
	if(hasHit(inky)){
		if(inky->scared){
			inky->die();
			newBonus();
		}else{
			die(blinky,pinky,inky,clyde);
		}
	}
	if(hasHit(clyde)){
		if(clyde->scared){
			clyde->die();
			newBonus();
		}else{
			die(blinky,pinky,inky,clyde);
		}
	}
	moveInDir();
	resetOff();
}

void player::newBonus(){
	bonuses.push_back(new bonus(gx+1.0*offx/OFFSET_RES,gy+1.0*offy/OFFSET_RES,lvl->GRID_W,lvl->GRID_H,50,bonusAmount));
	bonusAmount*=2;
}

