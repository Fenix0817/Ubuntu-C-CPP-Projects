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
#include "TracerGI.h"
#include "Material.h"
#include "MaterialMatte.h"
#include "MaterialEmmisive.h"
#include "MaterialReflective.h"
#include "Light.h"
#include "LightAmbient.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include <omp.h>
#include <chrono>
using namespace std::chrono;

Vector3 camPos=Vector3(1,0,0);
Vector3 lookAt=Vector3(0,0,0);
float zoom=1;

const int W=1000;
const int H=1000;

Tracer*tracer;

long curTime(){
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
	);
	return ms.count();
}

World*buildCornellBox(){
	camPos=Vector3(-.8,0,.9);//1,0,0
	lookAt=Vector3(1,0,0);
	zoom=1;

	World*world=new World();
	world->setBackground(Colors::white);
//	world->setDepth(10);

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

	MaterialEmmisive*matteLight=new MaterialEmmisive(30,Colors::white);

	Object*backWall=new ObjectPlane(Vector3(-1,0,0),Vector3(1,0,0));
	backWall->setMaterial(matteWhite);
	world->addObject(backWall);

	Object*leftWall=new ObjectPlane(Vector3(0,0,-1),Vector3(0,0,1));
	leftWall->setMaterial(matteRed);
	world->addObject(leftWall);

	Object*rightWall=new ObjectPlane(Vector3(0,0,1),Vector3(0,0,-1));
	rightWall->setMaterial(matteWhite);
	world->addObject(rightWall);

	Object*ceiling=new ObjectPlane(Vector3(0,1,0),Vector3(0,-1,0));
	ceiling->setMaterial(matteWhite);
	world->addObject(ceiling);

	Object*floor=new ObjectPlane(Vector3(0,-1,0),Vector3(0,1,0));
	floor->setMaterial(matteWhite);
	world->addObject(floor);

	Object*behindWall=new ObjectPlane(Vector3(3,0,0),Vector3(-1,0,0));
	behindWall->setMaterial(matteWhite);
	world->addObject(behindWall);

	Object*box1=new ObjectAABB(Vector3(-.8,-1,-.1),Vector3(0.3,1,0));
	box1->setMaterial(matteWhite);
	world->addObject(box1);

	Object*lightSphere=new ObjectSphere(Vector3(-.4,0,0.3),.2);
	lightSphere->setMaterial(matteLight);
	world->addObject(lightSphere);

	Light*ambient=new LightAmbient(0,Colors::white);
	world->setAmbient(ambient);

	return world;
}

World*buildBoxPlaneLight(){
	camPos=Vector3(-3,4,-4);
	lookAt=Vector3(0,0,0);
	zoom=1;

	World*world=new World();
	world->setBackground(Colors::black);
//	world->setDepth(10);

	MaterialMatte*matteWhite=new MaterialMatte();
	matteWhite->setAmbient(1,Colors::white);
	matteWhite->setDiffuse(1,Colors::white);

	MaterialMatte*matteRed=new MaterialMatte();
	matteRed->setAmbient(1,Colors::white);
	matteRed->setDiffuse(1,Colors::red);

	MaterialMatte*matteGreen=new MaterialMatte();
	matteGreen->setAmbient(1,Colors::white);
	matteGreen->setDiffuse(1,Colors::green);

	MaterialEmmisive*matteLight=new MaterialEmmisive(30,Colors::white-Colors::red*0.2f);

	MaterialReflective*matteReflective=new MaterialReflective();
	matteReflective->setReflective(1,Colors::white);
	matteReflective->setAmbient(1,Colors::white);

	Object*floor=new ObjectPlane(Vector3(0,0,0),Vector3(0,1,0));
	floor->setMaterial(matteWhite);
	world->addObject(floor);

	Object*top=new ObjectPlane(Vector3(0,4.1,0),Vector3(0,-1,0));
	top->setMaterial(matteWhite);
	world->addObject(top);

//	Object*box1=new ObjectAABB(Vector3(0,0,0),Vector3(1.5,1.5,1.5));
//	box1->setMaterial(matteRed);
//	world->addObject(box1);

	Object*sphere1=new ObjectSphere(Vector3(1.5,0,0),1);
	sphere1->setMaterial(matteReflective);
	world->addObject(sphere1);

	Object*box2=new ObjectAABB(Vector3(3,0,0),Vector3(8.5,1.5,3.5));
	box2->setMaterial(matteReflective);
	world->addObject(box2);

	Object*sphere2=new ObjectSphere(Vector3(1,1,1),1);
	sphere2->setMaterial(matteGreen);
	world->addObject(sphere2);

	Object*light=new ObjectSphere(Vector3(0,0.5,0),1);
	light->setMaterial(matteLight);
	world->addObject(light);

	Light*ambient=new LightAmbient(0,Colors::black);
	world->setAmbient(ambient);

	return world;
}

void init(){
//	World*world=buildCornellBox();
	World*world=buildBoxPlaneLight();
	world->setDepth(30);

	tracer=new TracerGI(world);

	world->tracer=tracer;
}

RGBColor mapColor(RGBColor color){
	if(color.x>1||color.y>1||color.z>1){
		color/=max(color.x,max(color.y,color.z));
	}
	return color;
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

	const int numSamples=10000;

	int num=0;
	const int total=W*H;

	long start,end;
	start=curTime();
#pragma omp parallel for
	for(int x=0;x<W;x++){
#pragma omp parallel for
		for(int y=0;y<H;y++){
			RGBColor color=Colors::black;
#pragma omp parallel for
			for(int i=0;i<numSamples;i++){
				color+=getColor(Vector2(x+randomFloat(),y+randomFloat())/Vector2(W,H));
			}
			color/=numSamples;
			color=mapColor(color);
			img.setPixel(x,y,color.x,color.y,color.z);
			num++;
		}
		printf("%i / %i\n",num,total);
	}
	end=curTime();
	printf("Time: %lu\n",end-start);
	//Around 830msms to 220ms for 1000x1000 simple pathtraced
	//OpenMP is MAGIC

	printf("Computed\n");

	img.clamp();
	img.save("pathtracing-05.ppm");
	img.dealloc();

	printf("Saved\n");

	return 0;
}
