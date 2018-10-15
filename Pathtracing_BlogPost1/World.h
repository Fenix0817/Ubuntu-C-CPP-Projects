/*
 * World.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "Object.h"
#include <vector>

struct World {
	std::vector<Object*>objects;
};

#endif /* WORLD_H_ */
