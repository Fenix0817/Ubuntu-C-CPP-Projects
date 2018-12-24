/*
 * Math.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef MATH_H_
#define MATH_H_

#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>

using glm::vec3;
using glm::vec2;

using glm::dot;
using glm::normalize;
using glm::cross;

inline float max(float a,float b){
	return a>b?a:b;
}

inline float min(float a,float b){
	return a<b?a:b;
}

inline float dot2(vec3 v){
	return dot(v,v);
}

#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define HALF_PI 1.57079632679
#define INV_PI 0.31830988618

#endif /* MATH_H_ */
