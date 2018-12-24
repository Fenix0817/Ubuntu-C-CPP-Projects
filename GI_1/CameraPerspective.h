/*
 * CameraPerspective.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef CAMERAPERSPECTIVE_H_
#define CAMERAPERSPECTIVE_H_

#include "Camera.h"

class CameraPerspective : public Camera {
public:
	CameraPerspective();
	virtual ~CameraPerspective();

	inline CameraPerspective(vec3 camPos,vec3 lookAt,vec2 size,float zoom){
		this->camPos=camPos;
		this->lookAt=lookAt;
		this->size=size;
		this->zoom=zoom;
		this->aspect=size.x/size.y;
		this->camUp=vec3(0,1,0);
	}

	vec3 camPos;
	vec3 camUp;
	vec3 lookAt;
	vec2 size;
	float zoom;
	float aspect;

	Ray getRay(vec2 uv);
};

#define CameraPerspective_withDir(p,d,s,z) CameraPerspective(p,p+d,s,z)

#endif /* CAMERAPERSPECTIVE_H_ */
