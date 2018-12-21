/*
 * ghost.h
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#ifndef GHOST_H_
#define GHOST_H_

#include "entity.h"

#include "utils.h"

class player;
class ghost;


class ghost : public entity {
public:
	ghost(level_ptr lvl);
	virtual ~ghost();

	int enterTime=0;
	bool scared=false;
	int scaredTime=0;

	virtual vec2 getTarget(player*pacman,ghost*blinky)=0;
	virtual vec3 getColor()=0;

	void scare();
	void die();
	void render();
	void update(player*pacman,ghost*blinky);


};

#endif /* GHOST_H_ */
