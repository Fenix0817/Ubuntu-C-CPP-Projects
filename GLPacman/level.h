/*
 * level.h
 *
 *  Created on: Dec 20, 2018
 *      Author: jack
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#define EMPTY 0
#define WALL 1
#define DOT 2
#define POWER_DOT 3

#include <cstdlib>

struct level {

	int GRID_W;
	int GRID_H;
	int**tiles;

	int PLAYER_X;
	int PLAYER_Y;
	int GHOST_X;
	int GHOST_Y;
	int GHOST_EXIT_X;
	int GHOST_EXIT_Y;

	inline void put_tiles(int**__level__){
		tiles=new int*[GRID_W];
		//Transpose the level because multidimensional arrays
		//are not in the right order in c++ (!!!!)
		for(int x=0;x<GRID_W;x++){
			tiles[x]=new int[GRID_H];
			for(int y=0;y<GRID_H;y++){
				tiles[x][y]=__level__[y][x];
			}
		}
	}

};

typedef level* level_ptr;

#endif /* LEVEL_H_ */
