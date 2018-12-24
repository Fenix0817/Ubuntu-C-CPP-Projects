/*
 * bonus.h
 *
 *  Created on: Dec 23, 2018
 *      Author: jack
 */

#ifndef BONUS_H_
#define BONUS_H_

#include "square.h"
#include "square_shader.h"
#include "Texture.h"

class bonus {
public:
	bonus(float x,float y,int w,int h,int l,int num);
	virtual ~bonus();

	float gx;
	float gy;
	int gw;
	int gh;
	int life;

	square_shader*shd;
	gl::Texture tex;

	void render();
	bool shouldDie();
	void step();
};

#endif /* BONUS_H_ */
