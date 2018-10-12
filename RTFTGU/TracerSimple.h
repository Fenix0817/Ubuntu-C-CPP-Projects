/*
 * TracerSimple.h
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#ifndef TRACERSIMPLE_H_
#define TRACERSIMPLE_H_

#include "Tracer.h"
	#include "tracerutils.h"
#include "utils.h"
#include "Object.h"
	#include "Plane.h"
	#include "Sphere.h"
#include "Material.h"
	#include "MaterialPhong.h"
	#include "Matte.h"
#include "Light.h"
	#include "LightAmbient.h"
	#include "LightDirectional.h"
	#include "LightPoint.h"

class TracerSimple : public Tracer {
public:
	TracerSimple();
	virtual ~TracerSimple();

	std::vector<Object*>world;
	std::vector<Light*>lights;

	Light*ambient;

	void create();
	RGBColor traceRay(Ray&ray);

};

#endif /* TRACERSIMPLE_H_ */
