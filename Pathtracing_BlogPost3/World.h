/*
 * World.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "Math.h"

class Object;
class Light;
class Tracer;

class World {
public:
	World();
	virtual ~World();

	std::vector<Object*>objects;
	std::vector<Light*>lights;

	Light*ambient;
	Tracer*tracer;

	RGBColor bgColor;

	int maxDepth;

	void addObject(Object*o);
	void addLight(Light*l);
	void setAmbient(Light*a);
	void setDepth(int d);
	void setBackground(RGBColor bg);
};

#endif /* WORLD_H_ */
