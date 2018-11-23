/*
 * TextAtlasPos.h
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#ifndef TEXTATLASPOS_H_
#define TEXTATLASPOS_H_

struct TextAtlasPos{
	float x,y,w,h;
	TextAtlasPos(float x,float y,float w,float h){
		this->x=x/w;
		this->y=(h-y-1)/h;
		this->w=1/w;
		this->h=1/h;
	}
};



#endif /* TEXTATLASPOS_H_ */
