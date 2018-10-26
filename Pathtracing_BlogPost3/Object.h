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

class Material;

class Object {
public:
	Object();
	virtual ~Object();

	virtual ShadeInfo hit(Ray ray)=0;
	virtual bool shadowHit(Ray ray)=0;

	Material*material;

	void setMaterial(Material*m);
};

#endif /* OBJECT_H_ */
