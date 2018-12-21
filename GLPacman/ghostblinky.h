/*
 * ghostblinky.h
 *
 *  Created on: Dec 21, 2018
 *      Author: jack
 */

#ifndef GHOSTBLINKY_H_
#define GHOSTBLINKY_H_

#include "ghost.h"
#include "player.h"

class ghost_blinky : public ghost {
public:
	ghost_blinky(level_ptr l);
	virtual ~ghost_blinky();


	vec3 getColor();
	vec2 getTarget(player*pacman,ghost*blinky);

};

#endif /* GHOSTBLINKY_H_ */
