/*
 * Object.h
 *
 *  Created on: Sep 28, 2018
 *      Author: jack
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "utils.h"

#include "ShadeInfo.h"
#include "Ray.h"

class Object {
public:
	Object();
	Object(Material*m);
	virtual ~Object();

	virtual ShadeInfo hit(Ray ray)=0;
	virtual bool shadowHit(Ray&ray)=0;

	Material* material;

};

#endif /* OBJECT_H_ */
