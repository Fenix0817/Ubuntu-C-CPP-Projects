/*
 * AtlasPos.h
 *
 *  Created on: Nov 3, 2018
 *      Author: jack
 */

#ifndef ATLASPOS_H_
#define ATLASPOS_H_

#include <glm/glm.hpp>

struct AtlasPos {
	glm::vec2 pos;
	glm::vec2 dim;
	AtlasPos(int x,int y,int sx,int sy,int w,int h){
		pos=glm::vec2(x,y)/glm::vec2(w,h);
		dim=glm::vec2(sx,sy)/glm::vec2(w,h);
	}
	glm::vec2 get00(){
		return pos;
	}
	glm::vec2 get10(){
		return pos+glm::vec2(1,0)*dim;
	}
	glm::vec2 get01(){
		return pos+glm::vec2(0,1)*dim;
	}
	glm::vec2 get11(){
		return pos+dim;
	}
};

#endif /* ATLASPOS_H_ */
