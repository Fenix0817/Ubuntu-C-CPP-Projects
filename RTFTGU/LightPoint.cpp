/*
 * LightPoint.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: jack
 */

#include "LightPoint.h"

LightPoint::LightPoint() {
	// TODO Auto-generated constructor stub

}

LightPoint::~LightPoint() {
	// TODO Auto-generated destructor stub
}

LightPoint::LightPoint(float i,RGBColor c,Vector3 p){
	intensity=i;
	color=c;
	pos=p;
}

Vector3 LightPoint::getDirection(ShadeInfo&si){
	return normalizeVector(pos-si.hitPoint);
}

RGBColor LightPoint::getColor(ShadeInfo&si){
	return intensity*color;
}
