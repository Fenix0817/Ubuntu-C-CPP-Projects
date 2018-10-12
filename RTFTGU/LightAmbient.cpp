/*
 * LightAmbient.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jack
 */

#include "LightAmbient.h"

LightAmbient::LightAmbient() {
	// TODO Auto-generated constructor stub

}

LightAmbient::LightAmbient(float i,RGBColor c){
	intensity=i;
	color = c;
}

LightAmbient::~LightAmbient() {
	// TODO Auto-generated destructor stub
}

Vector3 LightAmbient::getDirection(ShadeInfo&si){
	return Vector3(0);
}
RGBColor LightAmbient::getColor(ShadeInfo&si){
	return intensity*color;
}
