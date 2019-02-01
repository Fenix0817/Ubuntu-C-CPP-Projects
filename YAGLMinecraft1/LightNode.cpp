/*
 * LightNode.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: jack
 */

#include "LightNode.h"
#include "ChunkManager.h"

LightNode::LightNode(int x,int y,int z,ChunkManager*cm){
	pos=glm::ivec3(x,y,z);

	glm::ivec2 cpos=getChunkCoord(glm::ivec2(x,z));
	chunk=cm->getChunk(cpos.x,cpos.y,false);
}

