/*
 * Light.h
 *
 *  Created on: Nov 26, 2018
 *      Author: jack
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>
#include "LightNode.h"
#include <vector>
#include "Chunk.h"

class ChunkManager;

class Light {
public:
	Light();
	virtual ~Light();

	float df=0.2;

	glm::ivec3 pos;
	float val;

//	std::vector<LightNode*>nodes;
	std::vector<glm::ivec3>changes;

	std::vector<LightNode*>open;
	std::vector<LightNode*>closed;

	float getValue(int x,int y,int z);

	void initSpread(ChunkManager*cm);
	void stepSpread(ChunkManager*cm);

	bool isDone();

	void storeLight(ChunkManager*cm);

	bool needsUpdateOnAdd(int x,int y,int z);//Does this light need to be updated on block addition at (x,y,z)
	bool needsUpdateOnRem(int x,int y,int z);//Does this light need to be updated on block removal at (x,y,z)

};

#endif /* LIGHT_H_ */
