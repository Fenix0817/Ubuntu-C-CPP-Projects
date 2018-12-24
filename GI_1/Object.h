/*
 * Object.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Math.h"
#include "HitRes.h"

class Object {
public:
	Object();
	virtual ~Object();

	virtual HitRes hit(Ray r)=0;
};

#endif /* OBJECT_H_ */
