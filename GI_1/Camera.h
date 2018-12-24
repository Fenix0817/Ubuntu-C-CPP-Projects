/*
 * Camera.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Math.h"
#include "Ray.h"

class Camera {
public:
	Camera();
	virtual ~Camera();

	virtual Ray getRay(vec2 uv)=0;
};

#endif /* CAMERA_H_ */
