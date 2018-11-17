/*
 * Pathtracing.h
 *
 *  Created on: Oct 27, 2018
 *      Author: jack
 */

#ifndef PATHTRACING_H_
#define PATHTRACING_H_

#include <glm/glm.hpp>

#define OBJECT_PLANE 0
#define OBJECT_SPHERE 1

struct Material {
	glm::vec3 color;
	glm::vec3 light_color;
	float roughness;
};

struct Sphere {
	glm::vec3 pos;
	float rad;
	Material mat;
	Sphere(glm::vec3 p,float r,Material m){pos=p;rad=r;mat=m;}
};

struct Plane {
	glm::vec3 pos;
	glm::vec3 normal;
	Material mat;
	Plane(glm::vec3 p,glm::vec3 n,Material m){pos=p;normal=glm::normalize(n);mat=m;}
};

#endif /* PATHTRACING_H_ */
