/*
 * World.h
 *
 *  Created on: Oct 11, 2018
 *      Author: jack
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "utils.h"
#include "Object.h"
#include "Light.h"

class World {
public:
	World();
	virtual ~World();

	std::vector<Object*>objects;
	std::vector<Light*>lights;
	Light*ambientLight;

	void setAmbientLight(Light*light);
	void addLight(Light*light);
	void addObject(Object*object);
};

#endif /* WORLD_H_ */
