/*
 * utils.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#include "utils.h"


float lerp(float t,float a,float b){
	return (b-a)*t+a;
}
float norm(float t,float a,float b){
	return (t-a)/(b-a);
}
float map(float t,float s1,float e1,float s2,float e2){
	return lerp(norm(t,s1,e1),s2,e2);
}
