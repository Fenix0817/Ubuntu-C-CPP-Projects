/*
 * ObjectDisk.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef OBJECTDISK_H_
#define OBJECTDISK_H_

#include "Object.h"

class ObjectDisk : public Object {
public:
	ObjectDisk();
	virtual ~ObjectDisk();

	Vector3 center;
	Vector3 normal;
	float radius;

	ObjectDisk(Vector3 c,Vector3 n,float r);

	ShadeInfo hit(Ray ray);
};

#endif /* OBJECTDISK_H_ */
