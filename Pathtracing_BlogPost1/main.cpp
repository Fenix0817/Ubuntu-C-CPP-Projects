/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */


#include "ppm.h"
#include "Math.h"
#include "TracerUtils.h"
#include "World.h"
#include "Object.h"
#include "ObjectSphere.h"
#include "ObjectPlane.h"
#include "ObjectDisk.h"
#include "ObjectAABB.h"

const Vector3 camPos=Vector3(3,2,1);
const Vector3 lookAt=Vector3(0,0,0);
const float zoom=1;

const int W=1000;
const int H=1000;

World world;

void init(){
	world.objects.push_back(new ObjectSphere(Vector3(0,0,0),1));
	world.objects.push_back(new ObjectPlane(Vector3(0,0,0),Vector3(0,1,0)));
	world.objects.push_back(new ObjectDisk(Vector3(0,1.2,-2),Vector3(0.5,0.8,1),1));
	world.objects.push_back(new ObjectAABB(Vector3(-1,0,-1),Vector3(0.5,1.5,0)));
	world.objects.push_back(new ObjectPlane(Vector3(-1,0,0),Vector3(1,0,0)));
	world.objects.push_back(new ObjectPlane(Vector3(0,0,-3),Vector3(0,0,1)));
}

Vector3 getColor(Vector2 uv){
	uv*=2;
	uv-=1;
	uv.x*=W/H;

	Ray ray;
	ray.pos=camPos;

	Vector3 f=normalizeVector(lookAt-camPos);
	Vector3 r=crossVectors(Vector3(0,1,0),f);
	Vector3 u=crossVectors(f,r);

	Vector3 c=camPos+f*zoom;
	Vector3 i=c+uv.x*r+uv.y*u;
	ray.dir=normalizeVector(i-camPos);

	ShadeInfo si=intersectWorld(world,ray);
	if(!si.hit)return Vector3(0);
	Vector3 lightPos(5,4,3);
	Vector3 hitPoint=ray.pos+ray.dir*si.t;
	Vector3 normal=si.normal;
	float dotSN=dotVectors(normalizeVector(lightPos-hitPoint),normal);
//	return dotSN*(0.5f+0.5f*normal);
	return Vector3(dotSN);
}


int main(){
	printf("Start\n");
	ppm img;
	img.setSize(W,H);
	img.allocMem();

	init();

	printf("Memory allocated\n");

	for(int x=0;x<W;x++){
		for(int y=0;y<H;y++){
			Vector3 color=getColor(Vector2(x,y)/Vector2(W,H));
			img.setPixel(x,y,color.x,color.y,color.z);
		}
	}

	printf("Computed\n");

	img.clamp();
	img.save("pathtracing-01.ppm");
	img.dealloc();

	printf("Saved\n");

	return 0;
}
