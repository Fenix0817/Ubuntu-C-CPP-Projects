/*
 * LightDirectional.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jack
 */

#include "LightDirectional.h"

LightDirectional::LightDirectional() {
	// TODO Auto-generated constructor stub

}

LightDirectional::~LightDirectional() {
	// TODO Auto-generated destructor stub
}


LightDirectional::LightDirectional(float i,RGBColor c,Vector3 d){
	intensity=i;
	color=c;
	dir=normalizeVector(d);
}

RGBColor LightDirectional::getColor(ShadeInfo&si){
	return intensity*color;
}

Vector3 LightDirectional::getDirection(ShadeInfo&si){
	return dir;
}
