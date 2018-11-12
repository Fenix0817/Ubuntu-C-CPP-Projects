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

const int W=300;
const int H=300;

Tracer*tracer;
Object*sizedBox(Vector3 a,Vector3 b){
	return new ObjectAABB(a,a+b);
}
long curTime(){
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
	);
	return ms.count();
}

World*buildCornellBox(){
	camPos=Vector3(1,0,0);//1,0,0
	lookAt=Vector3(0,0,0);
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

	MaterialEmmisive*emmisive=new MaterialEmmisive(2,Colors::white);

	Object*backWall=new ObjectPlane(Vector3(-1,0,0),Vector3(1,0,0));
	backWall->setMaterial(matteOrange);
	world->addObject(backWall);

	Object*leftWall=new ObjectPlane(Vector3(0,0,-1),Vector3(0,0,1));
	leftWall->setMaterial(matteWhite);
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

//	Object*behindWall=new ObjectPlane(Vector3(1.1,0,0),Vector3(-1,0,0));
//	behindWall->setMaterial(matteWhite);
//	world->addObject(behindWall);

	Object*box1=sizedBox(Vector3(-1,.2,.2),Vector3(1,.4,.4));
	box1->setMaterial(matteGreen);
	world->addObject(box1);

	Object*lightSphere=new ObjectSphere(Vector3(-.7,0,0),.2);
	lightSphere->setMaterial(emmisive);
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

	MaterialMatte*white=new MaterialMatte();
	white->setAmbient(1,Colors::white);
	white->setDiffuse(1,Colors::white);

	MaterialMatte*red=new MaterialMatte();
	red->setAmbient(1,Colors::white);
	red->setDiffuse(1,Colors::red);

	MaterialMatte*green=new MaterialMatte();
	green->setAmbient(1,Colors::white);
	green->setDiffuse(1,Colors::green);

	MaterialEmmisive*emmisive=new MaterialEmmisive(90,Colors::white-Colors::red*0.2f);

	MaterialReflective*reflective=new MaterialReflective();
	reflective->setReflective(1,Colors::white);
	reflective->setAmbient(1,Colors::white);


	Object*light=new ObjectSphere(Vector3(0,1,0),1);
	light->setMaterial(emmisive);
	world->addObject(light);


	Object*ground=new ObjectPlane(Vector3(0,0,0),Vector3(0,1,0));
	ground->setMaterial(white);
	world->addObject(ground);

	Object*box=sizedBox(Vector3(2,0,2),Vector3(2,5,2));
	box->setMaterial(red);
	world->addObject(box);


	Light*ambient=new LightAmbient(0,Colors::black);
	world->setAmbient(ambient);

	return world;
}

World*buildSunAndBox(){
	World*world=new World();

	camPos=Vector3(60,30,60);
	lookAt=Vector3(0,0,0);
	zoom=1;

	//Materials
	Material*emmisive=new MaterialEmmisive(50,Colors::yellow);

	MaterialMatte*white=new MaterialMatte();
	white->setAmbient(0,Colors::black);
	white->setDiffuse(1,Colors::white);

	MaterialMatte*red=new MaterialMatte();
	red->setAmbient(0,Colors::black);
	red->setDiffuse(1,Colors::red);

	//Objects
	Object*ground=new ObjectPlane(Vector3(0,0,0),Vector3(0,1,0));
	ground->setMaterial(white);
	world->addObject(ground);

	float s=10;
	float h=70;
	float o=40;
//	Object*box1=new ObjectAABB(Vector3(o-s,0,-s),Vector3(o+s,h,s));
	Object*box1=new ObjectSphere(Vector3(30,30,0),40);
	box1->setMaterial(white);
	world->addObject(box1);

	//Lights
	Object*light=new ObjectDisk(Vector3(0,1,0),Vector3(1,0,0),50);
	light->setMaterial(emmisive);
	world->addObject(light);

	//Stuff that doesn't matter:
	Light*ambient=new LightAmbient(0,Colors::black);
	world->setAmbient(ambient);

	return world;
}

void init(){
//	World*world=buildCornellBox();
//	World*world=buildBoxPlaneLight();
	World*world=buildSunAndBox();
	world->setDepth(10);

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

	const int numSamples=500;
	const float numSamplesf=numSamples;

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
				color+=getColor(Vector2(x+randomFloat(),y+randomFloat())/Vector2(W,H))/numSamplesf;
			}
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
	img.save("pathtracing-08.ppm");
	img.dealloc();

	printf("Saved\n");

	return 0;
}
