/*
 * ghostpinky.h
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#ifndef GHOSTPINKY_H_
#define GHOSTPINKY_H_

#include "ghost.h"
#include "player.h"

class ghost_pinky : public ghost {
public:
	ghost_pinky(level_ptr l);
	virtual ~ghost_pinky();

	vec3 getColor();
	vec2 getTarget(player*pacman,ghost*blinky);
	int getEnterTime();
};

#endif /* GHOSTPINKY_H_ */
