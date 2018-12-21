/*
 * entity.h
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "level.h"
#include "square.h"
#include "square_shader.h"
#include "config.h"
#include "dir.h"

class entity {
public:
	entity(level_ptr l);
	virtual ~entity();

	level_ptr lvl;

	int gx;
	int gy;

	int offx;
	int offy;

	int speed;

	Dir dir;
	Dir nextDir;

	square_shader*shd;

	virtual void render()=0;

	void startRender();
	bool canMoveInDir(Dir d);
	void moveInDir();

	void resetOff();
};

#endif /* ENTITY_H_ */
