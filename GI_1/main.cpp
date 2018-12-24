/*
 * main.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#include "HitRes.h"
#include "Object.h"
#include "ObjectSphere.h"
#include "Camera.h"
#include "CameraPerspective.h"
#include "ImageBuilder.h"
#include "ImageBuilderMultisampled.h"
#include "Tracer.h"
#include "TracerGI.h"

const int W=500;
const int H=500;

const vec3 camPos=vec3(5,4,3);
const vec3 lookAt=vec3(0,0,0);
const float zoom=1;

const int numSamples=1;

int main(){
	Camera*camera=new CameraPerspective(camPos,lookAt,vec2(W,H),zoom);
	Tracer*tracer=new TracerGI(camera);
	ImageBuilder*ib=new ImageBuilderMultisampled(W,H,numSamples,tracer);
	ib->init();
	ib->buildImage();
	ib->save("gi-001.ppm");
	ib->end();
	return 0;
}

