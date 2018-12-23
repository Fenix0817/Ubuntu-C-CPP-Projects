/*
 * animator.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: jack
 */

#include "animator.h"

animator::animator(int s,int nf,std::string n) {
	// TODO Auto-generated constructor stub
	frame=0;
	speed=s;
	numFrames=nf;
	for(int i=0;i<numFrames;i++){
		std::string i_s=std::to_string(i);
		texL.push_back(gl::loadTexture("Textures/"+n+"-l"+i_s+".png"));
		texR.push_back(gl::loadTexture("Textures/"+n+"-r"+i_s+".png"));
		texU.push_back(gl::loadTexture("Textures/"+n+"-u"+i_s+".png"));
		texD.push_back(gl::loadTexture("Textures/"+n+"-d"+i_s+".png"));
	}
	shd=new square_shader("textured.frag");
}

animator::~animator() {
	// TODO Auto-generated destructor stub
}

void animator::render(int gx,int gy,int offx,int offy,Dir d,int gw,int gh){
	float dx=1.0f/gw;
	float dy=1.0f/gh;
	shd->render(    (gx+offx/OFFSET_RES-SPRITE_EXTRA)*dx, (gy+offy/OFFSET_RES-SPRITE_EXTRA)*dy,  (1.0+2.0*SPRITE_EXTRA)*dx,(1.0+2.0*SPRITE_EXTRA)*dy     );
	gl::Texture tex;
	if(d==DIR_L)tex=texL[(frame/speed)%numFrames];
	if(d==DIR_R)tex=texR[(frame/speed)%numFrames];
	if(d==DIR_U)tex=texU[(frame/speed)%numFrames];
	if(d==DIR_D)tex=texD[(frame/speed)%numFrames];
	tex.bindToUnit(0);
	shd->setInt("tex",0);
	renderSquare();
}

void animator::step(){
	frame++;
}
