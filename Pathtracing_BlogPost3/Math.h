/*
 * Math.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef MATH_H_
#define MATH_H_

#include <glm/glm.hpp>
#include <stdio.h>

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;

typedef Vector3 RGBColor;

#define HALF_PI 1.57079632679
#define TWO_PI 6.28318530718
#define PI 3.14159265359f
#define ONE_OVER_PI 0.31830988618f

namespace Colors {

const RGBColor white  (1,1,1);
const RGBColor black  (0,0,0);
const RGBColor red    (1,0,0);
const RGBColor green  (0,1,0);
const RGBColor blue   (0,0,1);
const RGBColor cyan   (0,1,1);
const RGBColor magenta(1,0,1);
const RGBColor yellow (1,1,0);

const RGBColor orange (1,.65,0);

}

inline float randomFloat(){
	return ((float)rand())/((float)RAND_MAX);
}

inline void swap(float&a,float&b){
	float t=a;
	a=b;
	b=t;
}

inline Vector3 normalizeVector(Vector3 a){
	return glm::normalize(a);
}

inline float squareLength(Vector3 a){
	return a.x*a.x+a.y*a.y+a.z*a.z;
}

inline float dotVectors2(Vector2 a,Vector2 b){
	return glm::dot(a,b);
}

inline float dotVectors(Vector3 a,Vector3 b){
	return glm::dot(a,b);
}

inline Vector3 crossVectors(Vector3 a,Vector3 b){
	return glm::cross(a,b);
}

inline float min(float a,float b){
	return a<b?a:b;
}

inline float max(float a,float b){
	return b<a?a:b;
}

inline float clamp(float t,float mi,float ma){
	if(t<mi)return mi;
	if(t>ma)return ma;
	return t;
}

inline Vector3 clamp(Vector3 t,float mi,float ma){
	return Vector3(clamp(t.x,mi,ma),clamp(t.y,mi,ma),clamp(t.z,mi,ma));
}

inline bool solvableQuadratic(float a,float b,float c){
	return b*b-4*a*c>=0;
}

inline bool solveQuadratic(float a,float b,float c,float&t1,float&t2){
	if(b*b-4*a*c<0)return false;
	float discr=sqrt(b*b-4*a*c);
	t1=(-b+discr)/(2*a);
	t2=(-b-discr)/(2*a);
	return true;
}

#endif /* MATH_H_ */
