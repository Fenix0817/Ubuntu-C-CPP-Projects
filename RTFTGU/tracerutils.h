/*
 * tracerutils.h
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#ifndef TRACERUTILS_H_
#define TRACERUTILS_H_

#include "ShadeInfo.h"
#include "Object.h"
#include <vector>
#include "World.h"

ShadeInfo intersect(World*world, Ray&ray);
bool shadowIntersect(World*world,Ray&ray);

#endif /* TRACERUTILS_H_ */
