/*
 * WorldGeneratorFlat.h
 *
 *  Created on: Feb 1, 2019
 *      Author: jack
 */

#ifndef WORLDGENERATORFLAT_H_
#define WORLDGENERATORFLAT_H_

#include "WorldGenerator.h"

class WorldGeneratorFlat: public WorldGenerator {
public:
	WorldGeneratorFlat();
	virtual ~WorldGeneratorFlat();

	void init();
	void generateData(int ox,int oz,Block data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]);
};

#endif /* WORLDGENERATORFLAT_H_ */
