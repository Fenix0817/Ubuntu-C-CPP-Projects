/*
 * MaterialEmmisive.h
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#ifndef MATERIALEMMISIVE_H_
#define MATERIALEMMISIVE_H_

#include "Material.h"

class MaterialEmmisive : public Material {
public:
	MaterialEmmisive();
	virtual ~MaterialEmmisive();

	float intensity;
	RGBColor color;

	MaterialEmmisive(float i,RGBColor c){
		intensity=i;
		color=c;
	}

	RGBColor shade(ShadeInfo&si);
	RGBColor giShade(ShadeInfo&si);
};

#endif /* MATERIALEMMISIVE_H_ */
