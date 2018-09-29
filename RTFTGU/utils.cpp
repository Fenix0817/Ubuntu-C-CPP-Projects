/*
 * utils.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: jack
 */

#include "utils.h"

float randomFloat(){
	return (1.0f*(rand()%RANDOM_ACCURACY))/RANDOM_ACCURACY;
}

bool solvableQuadratic(float a,float b,float c){
	return b*b-4*a*c>=0;
}

bool solveQuadratic(float a,float b,float c,float&r1,float&r2){
	float discr=sqrt(b*b-4*a*c);
	if(discr<0)return false;
	r1=(-b+discr)/(2*a);
	r2=(-b-discr)/(2*a);
	return true;
}

float squareLength(Vector3 v){
	return dotVector(v,v);
}

float dotVector(Vector3 a,Vector3 b){
	return glm::dot(a,b);
}

Vector3 normalizeVector(Vector3 v){
	return glm::normalize(v);
}
