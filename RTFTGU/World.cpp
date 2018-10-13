/*
 * World.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: jack
 */

#include "World.h"

World::World() {
	// TODO Auto-generated constructor stub

}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::setAmbientLight(Light*light){
	ambientLight=light;
}

void World::addLight(Light*light){
	lights.push_back(light);
}

void World::addObject(Object*object){
	objects.push_back(object);
}
