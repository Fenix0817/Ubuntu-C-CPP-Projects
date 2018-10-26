/*
 * MaterialMatte.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef MATERIALMATTE_H_
#define MATERIALMATTE_H_

#include "Material.h"
#include "Math.h"
#include "BRDFLambertian.h"
#include "ShadeInfo.h"
#include "World.h"

class MaterialMatte : public Material {
public:
	MaterialMatte();
	virtual ~MaterialMatte();

	RGBColor shade(ShadeInfo&si);

	BRDFLambertian*ambient;
	BRDFLambertian*diffuse;

	void setAmbient(float i,RGBColor c);
	void setDiffuse(float i,RGBColor c);
};

#endif /* MATERIALMATTE_H_ */
