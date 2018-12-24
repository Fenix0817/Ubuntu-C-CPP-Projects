/*
 * CameraPerspective.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#include "CameraPerspective.h"

CameraPerspective::CameraPerspective() {
	// TODO Auto-generated constructor stub

}

CameraPerspective::~CameraPerspective() {
	// TODO Auto-generated destructor stub
}

Ray CameraPerspective::getRay(vec2 uv){
	uv/=size;
	uv*=2;
	uv-=1;
	uv.x*=aspect;

	Ray ray;
	ray.pos=camPos;

	vec3 f=normalize(lookAt-camPos);
//	printf("f = %f,%f,%f\n",f.x,f.y,f.z);
//	printf("lookAt-camPos = %f,%f,%f\n",lookAt.x-camPos.x,lookAt.y-camPos.y,lookAt.z-camPos.z);
	vec3 r=cross(camUp,f);
	vec3 u=cross(f,r);

	vec3 c=camPos+f*zoom;
	vec3 i=c+uv.x*r+uv.y*u;
	ray.dir=normalize(i-camPos);
//	ray.dir=vec3(1,0,0);
	return ray;
}
