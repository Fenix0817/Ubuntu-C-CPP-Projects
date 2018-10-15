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
#include "World.h"
#include "LightAmbientOcclusion.h"
#include "MaterialUnshaded.h"
#include "Sampler.h"

//Raytracing From The Ground Up
//ISBN: 978-1-56881-272-4
//By Kevin Suffern
//
//This project is from following the book.
//You should get it.
//It is an awesome book!
//Explains everything really well.

const Vector3 camPos(2,1,1.5);
const Vector3 lookAt(0,0.5,0);
const float zoom=1;

const int w=150;
const int h=150;

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

	World*world=new World();

//	Matte*matGround=new Matte();
//	matGround->setAmbient(1,Colors::white);
//	matGround->setDiffuse(1,Colors::white);
//	MaterialPhong*matObject=new MaterialPhong();
//	matObject->setAmbient(1,Colors::white);
//	matObject->setDiffuse(1,Colors::green);
//	matObject->setSpecular(0.75,0.5f*Colors::green+0.5f*Colors::blue,40);
	MaterialUnshaded*matGround=new MaterialUnshaded();
	matGround->setColor(Colors::white);
	matGround->setAmbient(true);
	MaterialUnshaded*matWall1=new MaterialUnshaded();
	matWall1->setColor(Colors::white);
	matWall1->setAmbient(true);
	MaterialUnshaded*matWall2=new MaterialUnshaded();
	matWall2->setColor(Colors::blue);
	matWall2->setAmbient(true);
	MaterialUnshaded*matObject1=new MaterialUnshaded();
	matObject1->setColor(Colors::white);
	matObject1->setAmbient(true);
	MaterialUnshaded*matObject2=new MaterialUnshaded();
	matObject2->setColor(Colors::green);
	matObject2->setAmbient(true);
	world->addObject(new Plane(matGround,Vector3(0), Vector3(0,1,0)));
	world->addObject(new Sphere(matObject1,1, Vector3(0,1,0)));
	world->addObject(new Sphere(matObject2,0.75, Vector3(0.8,0.6,0)));
//	world->addObject(new Plane(matWall1,Vector3(0),Vector3(1,0,0)));
//	world->addObject(new Plane(matWall2,Vector3(0),Vector3(0,0,1)));

//	world->addLight(new LightPoint(1,Colors::red,Vector3(4)));
//	world->setAmbientLight(new LightAmbient(1,Colors::white));
	world->setAmbientLight(new LightAmbientOcclusion(1,Colors::white,0));

	tracer->world=world;

	int n=300;
	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
			RGBColor color;
			for(int i=0;i<n;i++)color+=getColor(tracer,x,y);
			color/=n;
			img.setPixel(x,y, color.x,color.y,color.z);
		}
		printf("Row %i out of %i done\n",x+1,w);
	}

	img.clamp();
	std::string fn="traced-09.ppm";
//	std::getline(std::cin,fn);
	img.save(fn);
	img.dealloc();
}
