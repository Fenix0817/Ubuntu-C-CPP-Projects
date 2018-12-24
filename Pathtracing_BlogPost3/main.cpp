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

const int W=200;
const int H=200;

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

World*buildBasicWorld(){
	camPos=Vector3(10,5,10);
	lookAt=Vector3(0,0,0);
	zoom=1;

	World*world=new World();
	world->setBackground(Colors::white);//TODO: Fix this


	MaterialMatte*matteWhite=new MaterialMatte();
	matteWhite->setDiffuse(1,Colors::white*0.8f+Colors::blue*0.2f);


	MaterialEmmisive*emmisive=new MaterialEmmisive(50,Colors::white);

	MaterialReflective*reflective=new MaterialReflective();
	reflective->setReflective(1,Colors::white);


	Object*ground=new ObjectPlane(Vector3(0,0,0),Vector3(0,1,0));
	ground->setMaterial(matteWhite);
	world->addObject(ground);

	Object*sphere1=new ObjectSphere(Vector3(-10,5,8),8);
	sphere1->setMaterial(reflective);
	world->addObject(sphere1);

	Object*sphere2=new ObjectSphere(Vector3(-5,0,0),3);
	sphere2->setMaterial(matteWhite);
	world->addObject(sphere2);

	Object*sphere3=new ObjectSphere(Vector3(-2,0,6),3);
	sphere3->setMaterial(matteWhite);
	world->addObject(sphere3);

//	Object*sphere4=new ObjectSphere(Vector3(1,0,-4),3);
//	sphere4->setMaterial(matteWhite);
//	world->addObject(sphere4);

	Object*light=new ObjectSphere(Vector3(10,6,0),6);
	light->setMaterial(emmisive);
	world->addObject(light);

//	Object*box=sizedBox(Vector3(-3,0,9),Vector3(9,8,4));
//	box->setMaterial(reflective);
//	world->addObject(box);




	return world;
}

void init(){
	World*world=buildBasicWorld();
	world->setDepth(10);

	tracer=new TracerGI(world);

	world->tracer=tracer;
}

RGBColor mapColor(RGBColor color){
//	if(color.x>1||color.y>1||color.z>1){
//		color/=max(color.x,max(color.y,color.z));
//	}
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


	RGBColor col=tracer->getColor(ray,0);
//	printf("%f,%f,%f\n",col.x,col.y,col.z);
	return mapColor(col);
//	return Colors::red;
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

	const int numSamples=50;
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
				RGBColor c=getColor(Vector2(x+randomFloat(),y+randomFloat())/Vector2(W,H));
//				printf("%f,%f,%f\n",c.x,c.y,c.z);
				color+=c;
			}
			color/=numSamplesf;
//			printf("%f,%f,%f\n",color.x,color.y,color.z);
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
	img.save("pathtracing-12.ppm");
	img.dealloc();

	printf("Saved\n");

	return 0;
}
