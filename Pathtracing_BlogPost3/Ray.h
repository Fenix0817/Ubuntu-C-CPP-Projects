/*
 * Ray.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef RAY_H_
#define RAY_H_

#include "Math.h"

struct Ray {
	Vector3 pos;
	Vector3 dir;
	Ray(){

	}
	Ray(Vector3 p,Vector3 d){
		pos=p;
		dir=d;
	}
};

#endif /* RAY_H_ */
