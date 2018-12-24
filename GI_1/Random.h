/*
 * Random.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include "Math.h"

inline int randomInt(){
	return rand();
}

inline float randomFloat(){
	return ((float)randomInt())/((float)RAND_MAX);
}

inline float randomFloat(float mi,float ma){
	return randomFloat()*(ma-mi)+mi;
}

inline vec2 randomUnitSquare(){
	return vec2(randomFloat(),randomFloat());
}

inline vec3 randomUnitSphere(){
	float t=randomFloat()*TWO_PI;
	float p=randomFloat()*PI;
	float s_t=sin(t);
	float c_p=cos(p);
	float s_p=sin(p);
	float c_t=cos(t);
	return vec3(s_t*c_p,s_t*s_p,c_t);
}

#endif /* RANDOM_H_ */
