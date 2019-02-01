/*
 * WorldGeneratorFlat.cpp
 *
 *  Created on: Feb 1, 2019
 *      Author: jack
 */

#include "WorldGeneratorFlat.h"

WorldGeneratorFlat::WorldGeneratorFlat() {
	// TODO Auto-generated constructor stub

}

WorldGeneratorFlat::~WorldGeneratorFlat() {
	// TODO Auto-generated destructor stub
}

void WorldGeneratorFlat::init(){

}
void WorldGeneratorFlat::generateData(int ox,int oz,Block data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]){
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int z=0;z<CHUNK_SIZE;z++){
			for(int y=6;y<CHUNK_HEIGHT;y++){
				data[x][y][z]=blockEmpty;
			}
			data[x][0][z]=data[x][1][z]=data[x][2][z]=blockStone;
			data[x][3][z]=data[x][4][z]=blockDirt;
			data[x][5][z]=blockGrass;
		}
	}
}
