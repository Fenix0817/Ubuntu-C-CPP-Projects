/*
 * ghostinky.h
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#ifndef GHOSTINKY_H_
#define GHOSTINKY_H_

#include "ghost.h"
#include "player.h"

class ghost_inky : public ghost {
public:
	ghost_inky(level_ptr l);
	virtual ~ghost_inky();

	vec3 getColor();
	vec2 getTarget(player*pacman,ghost*blinky);
	int getEnterTime();
};

#endif /* GHOSTINKY_H_ */
