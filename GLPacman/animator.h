/*
 * animator.h
 *
 *  Created on: Dec 22, 2018
 *      Author: jack
 */

#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Texture.h"
#include "square.h"
#include "config.h"
#include "dir.h"
#include <vector>
#include "square_shader.h"

class animator {
public:
	animator(int s,int nf,std::string name);
	virtual ~animator();

	int frame;
	int speed;
	int numFrames;

	square_shader*shd;

	std::vector<gl::Texture>texL,texR,texU,texD;

	void render(int gx,int gy,int offx,int offy,Dir d,int gw,int gh);
	void step();
};

#endif /* ANIMATOR_H_ */
