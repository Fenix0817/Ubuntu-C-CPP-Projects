/*
 * LightNode.h
 *
 *  Created on: Nov 23, 2018
 *      Author: jack
 */

#ifndef LIGHTNODE_H_
#define LIGHTNODE_H_


#include <glm/glm.hpp>

class Chunk;

struct LightNode{
	glm::ivec3 pos;//absolute position
	float val;
	bool spread;
};


#endif /* LIGHTNODE_H_ */
