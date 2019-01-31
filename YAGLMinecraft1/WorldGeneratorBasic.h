/*
 * WorldGeneratorBasic.h
 *
 *  Created on: Jan 31, 2019
 *      Author: jack
 */

#ifndef WORLDGENERATORBASIC_H_
#define WORLDGENERATORBASIC_H_

#include "WorldGenerator.h"
#include "FastNoise.h"
#include "Chunk.h"

class WorldGeneratorBasic: public WorldGenerator {
public:
	WorldGeneratorBasic();
	virtual ~WorldGeneratorBasic();

	FastNoise*fn;
	float zoom;

	void init();
	void generateData(int x,int z,Block data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]);
};

#endif /* WORLDGENERATORBASIC_H_ */
