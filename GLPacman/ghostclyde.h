/*
 * ghostclyde.h
 *
 *  Created on: Dec 22, 2018
 *      Author: jack
 */

#ifndef GHOSTCLYDE_H_
#define GHOSTCLYDE_H_

#include "ghost.h"
#include "player.h"

class ghost_clyde : public ghost {
public:
	ghost_clyde(level_ptr l);
	virtual ~ghost_clyde();

	vec2 getTarget(player*pacman,ghost*blinky);
	vec3 getColor();
	int getEnterTime();
};

#endif /* GHOSTCLYDE_H_ */
