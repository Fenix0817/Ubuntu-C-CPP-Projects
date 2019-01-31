/*
 * WorldGenerator.h
 *
 *  Created on: Jan 31, 2019
 *      Author: jack
 */

#ifndef SCREENSHOTS_WORLDGENERATOR_H_
#define SCREENSHOTS_WORLDGENERATOR_H_

#include "Block.h"
#include "ChunkConfig.h"

class WorldGenerator {
public:
	WorldGenerator();
	virtual ~WorldGenerator();

	virtual void init()=0;
	virtual void generateData(int x,int z,Block data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE])=0;
};

#endif /* SCREENSHOTS_WORLDGENERATOR_H_ */
