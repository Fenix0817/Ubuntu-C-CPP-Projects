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
#define GHOST_SLOWDOWN 4
#define GHOST_HOUSE_WALL 5

#include <cstdlib>
#include "utils.h"

struct level {

	int GRID_W;
	int GRID_H;
	int**tiles;
	bool**ghost_house_walls;
	bool**dots;
	bool**power_dots;

	int PLAYER_X;
	int PLAYER_Y;
	int GHOST_X;
	int GHOST_Y;
	int GHOST_EXIT_X;
	int GHOST_EXIT_Y;
	std::vector<vec2>ghost_noup;

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
		dots=new bool*[GRID_W];
		for(int x=0;x<GRID_W;x++){
			dots[x]=new bool[GRID_H];
			for(int y=0;y<GRID_H;y++){
				dots[x][y]=(tiles[x][y]==DOT);
			}
		}
		power_dots=new bool*[GRID_W];
		for(int x=0;x<GRID_W;x++){
			power_dots[x]=new bool[GRID_H];
			for(int y=0;y<GRID_H;y++){
				power_dots[x][y]=(tiles[x][y]==POWER_DOT);
			}
		}
		ghost_house_walls=new bool*[GRID_W];
		for(int x=0;x<GRID_W;x++){
			ghost_house_walls[x]=new bool[GRID_H];
			for(int y=0;y<GRID_H;y++){
				if(tiles[x][y]==GHOST_HOUSE_WALL){
					ghost_house_walls[x][y]=true;
					tiles[x][y]=WALL;
				}else{
					ghost_house_walls[x][y]=false;
				}
			}
		}
	}

};

typedef level* level_ptr;

#endif /* LEVEL_H_ */
