/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include <math.h>
#include "ppm.h"

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

int main(){

#pragma omp for
	for(int i=0;i<10;i++){
		printf("%i\n",i);
	}
//	int w=1000;
//	int h=1000;
//	ppm img;
//	img.setSize(w,h);
//	img.allocMem();
//
//#pragma omp parallel for ordered schedule(dynamic)
//	for(int x=0;x<w;x++){
//#pragma omp parallel for ordered schedule(dynamic)
//		for(int y=0;y<h;y++){
//			printf("%i %i\n",x,y);
//			float fx=x;
//			float fy=y;
//			fx/=w;
//			fy/=h;
//			fx*=4;
//			fy*=4;
//			fx-=2;
//			fy-=2;
//
//			complex c=fromXY(fx,fy);
//			complex c0=c;
//
//			int max=50;
//			int i=0;
//			for(i=0;i<max&&c.r<10000;i++){
//				c=c^2;
//				c=c+c0;
//			}
//			float f=((float)i)/((float)max);
//			img.setPixel(x,y,f);
//		}
//	}
//
//	img.clamp();
//	img.save("mandelbrot.ppm");
//	img.dealloc();

	return 0;
}
