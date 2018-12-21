/*
 * entity.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#include "entity.h"

entity::entity(level_ptr l) {
	gx=-1;
	gy=-1;
	lvl=l;
	dir=DIR_L;
	nextDir=DIR_L;
	speed=0;
	offx=0;
	offy=0;
	shd=new square_shader("color.frag");
}

entity::~entity() {
	// TODO Auto-generated destructor stub
}

void entity::startRender(){
	float dx=1.0/lvl->GRID_W;
	float dy=1.0/lvl->GRID_H;
	float r=OFFSET_RES;
	shd->render( (gx+offx/r)*dx,(gy+offy/r)*dy,dx,dy);
}

bool entity::canMoveInDir(Dir d){
	int x=get_x(d)+gx;
	int y=get_y(d)+gy;
	if(x<0||y<0||x>=lvl->GRID_W||y>=lvl->GRID_H)return true;
	return lvl->tiles[x][y]!=WALL;
}

void entity::moveInDir(){
	if(canMoveInDir(dir)){
		offx+=get_x(dir)*speed;
		offy+=get_y(dir)*speed;
	}
}

void entity::resetOff(){
	if(offx<-OFFSET_RES){
		gx-=1;
		offx=0;
	}
	if(offx>OFFSET_RES){
		gx+=1;
		offx=0;
	}
	if(offy<-OFFSET_RES){
		gy-=1;
		offy=0;
	}
	if(offy>OFFSET_RES){
		gy+=1;
		offy=0;
	}

	if(offx==0&&offy==0){
		if(gx<0&&dir==DIR_L){
			gx=lvl->GRID_W-1;
		}
		if(gx>=lvl->GRID_W&&dir==DIR_R){
			gx=0;
		}
	}
}
