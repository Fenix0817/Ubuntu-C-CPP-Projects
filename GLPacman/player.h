/*
 * player.h
 *
 *  Created on: Dec 20, 2018
 *      Author: jack
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"
#include "ghost.h"
#include "animator.h"
#include "bonus.h"

class player : public entity {
public:
	player(level_ptr lvl);
	virtual ~player();

	animator*anim;

	std::vector<bonus*>bonuses;
	int bonusAmount=200;

	void render();
	void update(ghost*blinky,ghost*pinky,ghost*inky,ghost*clyde);
	bool hasHit(ghost*g);
	void die(ghost*blinky,ghost*pinky,ghost*inky,ghost*clyde);
	void newBonus();
};

#endif /* PLAYER_H_ */
