/*
 * World.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

class Object;
class Light;

class World {
public:
	World();
	virtual ~World();

	std::vector<Object*>objects;
	std::vector<Light*>lights;

	Light*ambient;

	void addObject(Object*o);
	void addLight(Light*l);
	void setAmbient(Light*a);
};

#endif /* WORLD_H_ */
