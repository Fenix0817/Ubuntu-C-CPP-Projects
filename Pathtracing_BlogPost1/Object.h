/*
 * Object.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Math.h"
#include "Ray.h"
#include "ShadeInfo.h"

class Object {
public:
	Object();
	virtual ~Object();

	virtual ShadeInfo hit(Ray ray)=0;
};

#endif /* OBJECT_H_ */
