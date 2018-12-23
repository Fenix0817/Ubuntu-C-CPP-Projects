/*
 * ghost.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#include "ghost.h"

ghost::ghost(level_ptr l,std::string name) : entity(l) {
	// TODO Auto-generated constructor stub
	speed=GHOST_SPEED;
	gx=l->GHOST_X;
	gy=l->GHOST_Y;
	anim=new animator(4,2,name);
	animWhite=new animator(7,2,"ghostwhite");
	animBlue=new animator(7,2,"ghostblue");
	animEyes=new animator(1,1,"ghosteyes");
}

ghost::~ghost() {
	// TODO Auto-generated destructor stub
}

void ghost::reset(){
	enterTime=getEnterTime();
	scared=false;
	scaredTime=0;
	gx=lvl->GHOST_X;
	gy=lvl->GHOST_Y;
	speed=GHOST_SPEED;
	offx=0;
	offy=0;
}

void ghost::scare(){
	scared=true;
	scaredTime=SCARE_TIME;
	if(canMoveInDir(get_opp(dir))){
		dir=get_opp(dir);
	}
}

void ghost::die(){
	gx=lvl->GHOST_X;
	gy=lvl->GHOST_Y;
	scared=false;
	scaredTime=0;
	enterTime=GHOST_DEATH_ENTER_TIME;
	speed=GHOST_SPEED;
	offx=0;
	offy=0;
}

void ghost::render(){
//	startRender();
//	vec3 col=getColor();
//	shd->setVec3("color",std::get<0>(col),std::get<1>(col),std::get<2>(col));
//	if(scared){
//		shd->setVec3("color",0,0,1);
//		if(scaredTime<FLASH_TIME&&  (scaredTime/FLASH_SPEED)%2==0  ){
//			shd->setVec3("color",1,1,1);
//		}
//	}
//	renderSquare();

	animator*a=anim;
	if(scared){
		if(scaredTime<FLASH_TIME&&(scaredTime/FLASH_SPEED)%2==0){
			a=animWhite;
		}else{
			a=animBlue;
		}
	}

	a->render(gx,gy,offx,offy,dir,lvl->GRID_W,lvl->GRID_H);
	anim->step();
	animWhite->step();
	animBlue->step();
}

void ghost::update(player*pacman,ghost*blinky){
	if(scared){
		speed=SCARED_GHOST_SPEED;
		scaredTime-=1;
		if(scaredTime<0){
			scared=false;
		}
	}else{
		speed=GHOST_SPEED;
		if(lvl->tiles[gx][gy]==GHOST_SLOWDOWN){
			speed=GHOST_SLOWDOWN_SPEED;
		}
	}
	enterTime-=1;
	if(enterTime>0){
//		return;
	}else if(enterTime==0){
		gx=lvl->GHOST_EXIT_X;
		gy=lvl->GHOST_EXIT_Y;
	}

	resetOff();

	std::vector<Dir>allDirs={DIR_L,DIR_R,DIR_U,DIR_D};
	if(scared){
		std::vector<Dir>dirs;
		for(int i=0;i<4;i++){
			if(canMoveInDir(allDirs[i])&&!is_opp(allDirs[i],dir))dirs.push_back(allDirs[i]);
		}
		nextDir=dirs[ rand()%dirs.size() ];
	}else{
		if(offx==0&&offy==0){
			vec2 target=getTarget(pacman,blinky);
			if(enterTime>0){
				target={  rand()%100-50,rand()%100-50  };
			}
			std::vector<Dir>dirs;
			for(int i=0;i<4;i++){
				if(canMoveInDir(allDirs[i])&&!is_opp(allDirs[i],dir)){
					dirs.push_back(allDirs[i]);
				}
			}

			bool noUp=false;
			for(int i=0;i<lvl->ghost_noup.size();i++){
				vec2 v=lvl->ghost_noup[i];
				if(std::get<0>(v)==gx&&std::get<1>(v)==gy){
					noUp=true;
				}
			}
			if(noUp){
				int index=-1;
				for(int i=0;i<dirs.size();i++){
					if(dirs[i]==DIR_U){
						index=i;
					}
				}
				if(index!=-1){
					dirs.erase(dirs.begin()+index);
				}
			}
			std::vector<float>weights;
			for(int i=0;i<dirs.size();i++){
				float x0=std::get<0>(target);
				float y0=std::get<1>(target);
				float x1=gx+get_x(dirs[i]);
				float y1=gy+get_y(dirs[i]);
				weights.push_back( (x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)  );
			}
			int minIndex=0;
			for(int i=1;i<dirs.size();i++){
				if(weights[i]<weights[minIndex]){
					minIndex=i;
				}
			}
			nextDir=dirs[minIndex];

		}
	}
	if(canMoveInDir(nextDir)&&offx==0&&offy==0){
		dir=nextDir;
	}
	moveInDir();
	resetOff();
}
