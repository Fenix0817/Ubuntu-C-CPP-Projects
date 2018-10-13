/*
 * MaterialUnshaded.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: jack
 */

#include "MaterialUnshaded.h"

MaterialUnshaded::MaterialUnshaded() {
	// TODO Auto-generated constructor stub

}

MaterialUnshaded::~MaterialUnshaded() {
	// TODO Auto-generated destructor stub
}

RGBColor MaterialUnshaded::shade(ShadeInfo&si){
	if(ambient)return color*si.world->ambientLight->getColor(si);
	return color;
}

void MaterialUnshaded::setColor(RGBColor c){
	color=c;
}

void MaterialUnshaded::setAmbient(bool a){
	ambient=a;
}


