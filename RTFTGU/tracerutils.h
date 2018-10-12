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

ShadeInfo intersect(std::vector<Object*>&list, Ray&ray);

#endif /* TRACERUTILS_H_ */
