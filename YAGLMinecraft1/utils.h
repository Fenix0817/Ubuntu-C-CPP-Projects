/*
 * utils.h
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <glm/glm.hpp>

float lerp(float t,float a,float b);
float norm(float t,float a,float b);
float map(float t,float s1,float e1,float s2,float e2);

const float PI=3.14159265359;


namespace glm {

typedef glm::vec<2,int,glm::qualifier::defaultp> vec2i;

}

#endif /* UTILS_H_ */
