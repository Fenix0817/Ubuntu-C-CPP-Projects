/*
 * bonus.cpp
 *
 *  Created on: Dec 23, 2018
 *      Author: jack
 */

#include "bonus.h"

bonus::bonus(float x,float y,int w,int h,int l,int num){
	gx=x;
	gy=y;
	gw=w;
	gh=h;
	life=l;
	shd=new square_shader("textured.frag");
	tex=gl::loadTexture("Textures/bonus-"+std::to_string(num)+".png");
}

bonus::~bonus() {
	// TODO Auto-generated destructor stub
}

void bonus::render(){
	shd->render(1.0*gx/gw,1.0*gy/gh,1.0/gw,1.0/gh);
	shd->setInt("tex",0);
	tex.bindToUnit(0);
	renderSquare();
}
bool bonus::shouldDie(){
	return life<0;
}

void bonus::step(){
	printf("1: %i\n",life);
	life-=1;
	printf("2: %i\n",life);
}
