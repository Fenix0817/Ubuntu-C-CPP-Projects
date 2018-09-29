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

//Raytracing From The Ground Up
//ISBN: 978-1-56881-272-4
//By Kevin Suffern
//
//This project is from following the book.
//You should get it.
//It is an awesome book!
//Explains everything really well.

int main(){
	//TODO: Camera class, plane class, tracer class.....

	std::vector<Object*>world;
	world.push_back(new Sphere(1,Vector3(0,0,0)));
	world.push_back(new Plane(Vector3(0),Vector3(0,1,0)));

	int w=500;
	int h=500;

	ppm img;
	img.setSize(w,h);
	img.allocMem();

	Vector3 camPos=Vector3(2,1,3);
	Vector3 lookAt=Vector3(0,0,0);
	float zoom=1;

	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
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

			ShadeInfo si;
			si.hit=false;
			for(Object*obj:world){
				ShadeInfo nsi=obj->hit(ray);
				if(nsi.hit){
					if(!si.hit)si=nsi;
					else {
						if(si.t>nsi.t)si=nsi;
					}
				}
			}

			if(si.hit){
				float f=dotVector(si.normal,normalizeVector(Vector3(2,2,2)-ray.pos-ray.dir*si.t));
//				img.setPixel(x,y,si.normal.x*0.5+0.5,si.normal.y*0.5+0.5,si.normal.z*0.5+0.5);
				img.setPixel(x,y,f);
			}else{
				img.setPixel(x,y,0);
			}
		}
	}

	img.clamp();
	img.save("traced-01.ppm");
	img.dealloc();
}
