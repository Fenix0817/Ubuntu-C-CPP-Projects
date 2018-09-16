/*
 * TexturePos.h
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#ifndef TEXTUREPOS_H_
#define TEXTUREPOS_H_

#include <glm/glm.hpp>

struct TexturePos {
	glm::vec2 _00,_01,_10,_11;
	TexturePos(int x,int y,int w,int h){
		_00=glm::vec2(x,y);
		_01=glm::vec2(x,y+1);
		_10=glm::vec2(x+1,y);
		_11=glm::vec2(x+1,y+1);
		glm::vec2 s(w,h);
		_00/=s;
		_01/=s;
		_10/=s;
		_11/=s;
		float o=0;
		_00+=glm::vec2( o, o);
		_01+=glm::vec2( o,-o);
		_10+=glm::vec2(-o, o);
		_11+=glm::vec2(-o,-o);
	}
};

#endif /* TEXTUREPOS_H_ */
