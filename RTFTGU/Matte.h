/*
 * Matte.h
 *
 *  Created on: Oct 9, 2018
 *      Author: jack
 */

#ifndef MATTE_H_
#define MATTE_H_

#include "Material.h"
#include "Colors.h"
#include "BRDF.h"
#include "BRDFLambertian.h"
#include "Ray.h"

class Matte : public Material {
public:
	Matte();
	virtual ~Matte();

	RGBColor shade(ShadeInfo&si);

	BRDFLambertian* ambient;
	BRDFLambertian* diffuse;

	void setAmbient(float i,RGBColor c);
	void setDiffuse(float i,RGBColor c);

};

#endif /* MATTE_H_ */
