/*
 * complex.h
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <cmath>

struct complex{
	float theta,r;
};

float getX(complex c){
	return c.r*cos(c.theta);
}

float getY(complex c){
	return c.r*sin(c.theta);
}

complex fromXY(float x,float y){
	return {atan2(y,x),sqrt(x*x+y*y)};
}

complex operator+(complex a,complex b){
	return fromXY(getX(a)+getX(b),getY(a)+getY(b));
}

complex operator-(complex a,complex b){
	return fromXY(getX(a)-getX(b),getY(a)-getY(b));
}

complex operator*(float a,complex b){
	return {b.theta,a*b.r};
}

complex operator*(complex a,float b){
	return {a.theta,b*a.r};
}

complex operator/(complex a,float b){
	return {a.theta,a.r/b};
}

complex operator^(complex a,float b){
	return {a.theta*b,pow(a.r,b)};
}



#endif /* COMPLEX_H_ */
