/*
 * LightNode.h
 *
 *  Created on: Jan 31, 2019
 *      Author: jack
 */

#ifndef LIGHTNODE_H_
#define LIGHTNODE_H_

#include <glm/glm.hpp>

class Chunk;

struct LightNode{
	glm::ivec3 pos;
	Chunk*chunk;
};


#endif /* LIGHTNODE_H_ */
