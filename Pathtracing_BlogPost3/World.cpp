/*
 * World.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "World.h"

World::World() {
	// TODO Auto-generated constructor stub

}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addObject(Object*o){
	objects.push_back(o);
}

void World::addLight(Light*l){
	lights.push_back(l);
}

void World::setAmbient(Light*a){
	ambient=a;
}
