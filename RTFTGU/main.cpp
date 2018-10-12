/*
 * main.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: jack
 */

#include "utils.h"

#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Tracer.h"
#include "TracerSimple.h"
#include "TracerSphereSampling.h"

//Raytracing From The Ground Up
//ISBN: 978-1-56881-272-4
//By Kevin Suffern
//
//This project is from following the book.
//You should get it.
//It is an awesome book!
//Explains everything really well.

const Vector3 camPos(2,0.5,1.3);
const Vector3 lookAt(0,0,0);
const float zoom=1;

const int w=500;
const int h=500;

RGBColor getColor(Tracer*tracer,int x,int y){
	Vector2 uv(x,y);
	uv.x/=w;
	uv.y/=h;
	uv*=2;
	uv-=1;
	uv.x*=w/h;
	Ray ray;
	ray.pos=camPos;

	Vector3 f=normalizeVector(lookAt-camPos);
	Vector3 r=crossVector(Y_AXIS,f);
	Vector3 u=crossVector(f,r);

	Vector3 c=camPos+f*zoom;
	Vector3 i=c+uv.x*r+uv.y*u;
	ray.dir=normalizeVector(i-camPos);

	return tracer->traceRay(ray);
}

int main(){

	ppm img;
	img.setSize(w,h);
	img.allocMem();

	Tracer* tracer = new TracerSimple();
	tracer->create();

	int samples=30;

	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
			RGBColor color=getColor(tracer,x,y);
			img.setPixel(x,y, color.x,color.y,color.z);
		}
		printf("Row %i out of %i done\n",x+1,w);
	}

	img.clamp();
	std::string fn="traced-03.ppm";
//	std::getline(std::cin,fn);
	img.save(fn);
	img.dealloc();
}
