/*
 * ObjectPlane.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef OBJECTPLANE_H_
#define OBJECTPLANE_H_

#include "Object.h"

class ObjectPlane : public Object {
public:
	ObjectPlane();
	virtual ~ObjectPlane();

	Vector3 pos;
	Vector3 normal;

	ObjectPlane(Vector3 p,Vector3 n);

	ShadeInfo hit(Ray ray);
};

#endif /* OBJECTPLANE_H_ */
