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
#include "Tracer.h"
#include "TracerSimple.h"
#include "Material.h"
#include "MaterialMatte.h"
#include "Light.h"
#include "LightAmbient.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include <omp.h>
#include <chrono>
using namespace std::chrono;

const Vector3 camPos=Vector3(2,0,0);
const Vector3 lookAt=Vector3(0,0,0);
const float zoom=1;

const int W=1000;
const int H=1000;

Tracer*tracer;

long curTime(){
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
	);
	return ms.count();
}

void init(){
//	world.objects.push_back(new ObjectSphere(Vector3(0,0,0),1));
//	world.objects.push_back(new ObjectPlane(Vector3(0,0,0),Vector3(0,1,0)));
//	world.objects.push_back(new ObjectDisk(Vector3(0,1.2,-2),Vector3(0.5,0.8,1),1));
//	world.objects.push_back(new ObjectAABB(Vector3(-1,0,-1),Vector3(0.5,1.5,0)));
//	world.objects.push_back(new ObjectPlane(Vector3(-1,0,0),Vector3(1,0,0)));
//	world.objects.push_back(new ObjectPlane(Vector3(0,0,-3),Vector3(0,0,1)));
	World*world=new World();

	MaterialMatte*matteWhite=new MaterialMatte();
	matteWhite->setAmbient(1,Colors::white);
	matteWhite->setDiffuse(1,Colors::white);

	MaterialMatte*matteGreen=new MaterialMatte();
	matteGreen->setAmbient(1,Colors::white);
	matteGreen->setDiffuse(1,Colors::green);

	MaterialMatte*matteRed=new MaterialMatte();
	matteRed->setAmbient(1,Colors::white);
	matteRed->setDiffuse(1,Colors::red);

	MaterialMatte*matteOrange=new MaterialMatte();
	matteOrange->setAmbient(1,Colors::white);
	matteOrange->setDiffuse(1,Colors::orange);

	Object*backWall=new ObjectPlane(Vector3(-1,0,0),Vector3(1,0,0));
	backWall->setMaterial(matteWhite);
	world->addObject(backWall);

	Object*leftWall=new ObjectPlane(Vector3(0,0,-1),Vector3(0,0,1));
	leftWall->setMaterial(matteRed);
	world->addObject(leftWall);

	Object*rightWall=new ObjectPlane(Vector3(0,0,1),Vector3(0,0,-1));
	rightWall->setMaterial(matteGreen);
	world->addObject(rightWall);

	Object*ceiling=new ObjectPlane(Vector3(0,1,0),Vector3(0,-1,0));
	ceiling->setMaterial(matteWhite);
	world->addObject(ceiling);

	Object*floor=new ObjectPlane(Vector3(0,-1,0),Vector3(0,1,0));
	floor->setMaterial(matteWhite);
	world->addObject(floor);

	Object*box1=new ObjectAABB(Vector3(-.7,-1,-.6),Vector3(-.1,0,-.1));
	box1->setMaterial(matteOrange);
	world->addObject(box1);

	Light*ambient=new LightAmbient(0	,Colors::white);
	world->setAmbient(ambient);

	Light*light=new LightPoint(3,Colors::white,Vector3(0.3,0,0));
	world->addLight(light);

	tracer=new TracerSimple(world);
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

	return tracer->getColor(ray);
}


int main(){
	printf("Start\n");
	ppm img;
	img.setSize(W,H);
	img.allocMem();

	init();

	printf("Memory allocated\n");

	//TODO: Bring sampler classes over from RTFTGU
	//TODO: Soft shadows
	//TODO: Delete all light classes
	//TODO: TracerSoftShadows
	//TODO: ObjectLight: base class for 3d lights
	//TODO: ObjectLightSphere: spherical light
	//TODO: World:
	//TODO: 	- std::vector<Object*>objects;
	//TODO:		- std::vector<ObjectLight*>lights;

	long start,end;
	start=curTime();
#pragma omp parallel for
	for(int x=0;x<W;x++){
#pragma omp parallel for
		for(int y=0;y<H;y++){
			Vector3 color=getColor(Vector2(x,y)/Vector2(W,H));
			if(color.x>1||color.y>1||color.z>1){
				color/=max(color.x,max(color.y,color.z));
			}
			img.setPixel(x,y,color.x,color.y,color.z);
		}
	}
	end=curTime();
	printf("Time: %lu\n",end-start);
	//Around 830msms to 220ms for 1000x1000 simple pathtraced
	//OpenMP is MAGIC

	printf("Computed\n");

	img.clamp();
	img.save("pathtracing-01.ppm");
	img.dealloc();

	printf("Saved\n");

	return 0;
}
