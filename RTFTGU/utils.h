/*
 * utils.h
 *
 *  Created on: Sep 27, 2018
 *      Author: jack
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <glm/glm.hpp>
#include "ppm.h"
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#define RANDOM_ACCURACY RAND_MAX

typedef glm::mat2 Matrix2;
typedef glm::mat3 Matrix3;
typedef glm::mat4 Matrix4;
typedef glm::vec3 Vector3;
typedef glm::vec3 RGBColor;
typedef glm::vec3 Normal;

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

float randomFloat();

bool solvableQuadratic(float a,float b,float c);

bool solveQuadratic(float a,float b,float c,float&r1,float&r2);

float squareLength(Vector3 v);

float dotVector(Vector3 a,Vector3 b);

Vector3 normalizeVector(Vector3 v);

#endif /* UTILS_H_ */
