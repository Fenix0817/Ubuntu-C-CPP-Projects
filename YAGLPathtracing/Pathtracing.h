/*
 * Pathtracing.h
 *
 *  Created on: Oct 27, 2018
 *      Author: jack
 */

#ifndef PATHTRACING_H_
#define PATHTRACING_H_

#include <glm/glm.hpp>

#define MATERIAL_MATTE 0
#define MATERIAL_PHONG 1

#define BRDF_LAMBERTIAN 0
#define BRDF_GLOSSY_SPECULAR 1

#define OBJECT_PLANE 0
#define OBJECT_SPHERE 1


struct BRDF {
	//lambertian
	float lambertian_intensity;
	glm::vec3 lambertian_color;

	//glossy specular
	float glossy_specular_intensity;
	glm::vec3 glossy_specular_color;
	float glossy_specular_exp;

	int type;
};

struct Material {
	//matte
	BRDF matte_ambient;
	BRDF matte_diffuse;

	//phong
	BRDF phong_ambient;
	BRDF phong_diffuse;
	BRDF phong_specular;

	int type;
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
