/*
 * player.h
 *
 *  Created on: Dec 20, 2018
 *      Author: jack
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"

class player : public entity {
public:
	player(level_ptr lvl);
	virtual ~player();

	void render();
	void update();
};

#endif /* PLAYER_H_ */
