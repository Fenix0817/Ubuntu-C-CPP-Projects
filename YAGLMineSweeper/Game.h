/*
 * Game.h
 *
 *  Created on: Oct 24, 2018
 *      Author: jack
 */

#ifndef GAME_H_
#define GAME_H_

//TRUE=1
//FALSE=0

#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Game {
public:
	Game();
	virtual ~Game();

	bool**bombs;
	bool**revealed;
	bool**flagged;

	int gw;
	int gh;

	int numBombs;

	bool inBounds(int x,int y);

	bool getBomb(int x,int y);
	int getNear(int x,int y);
	int getRevealedNear(int x,int y);
	int getFlaggedNear(int x,int y);

	void placeMines(int numMines,int safeX,int safeY);

	void initBoard(int w,int h);
	void flag(int x,int y);
	void reveal(int x,int y);

	int getTileWidth(int w);
	int getTileHeight(int h);

	void free();

};

#endif /* GAME_H_ */
