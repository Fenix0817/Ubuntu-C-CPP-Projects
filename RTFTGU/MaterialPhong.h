/*
 * MaterialPhong.h
 *
 *  Created on: Oct 10, 2018
 *      Author: jack
 */

#ifndef MATERIALPHONG_H_
#define MATERIALPHONG_H_

#include "Material.h"
#include "Colors.h"
#include "BRDF.h"
#include "BRDFLambertian.h"
#include "BRDFGlossySpecular.h"
#include "Ray.h"

class MaterialPhong : public Material {
public:
	MaterialPhong();
	virtual ~MaterialPhong();

	RGBColor shade(ShadeInfo&si);

	BRDFLambertian*ambient;
	BRDFLambertian*diffuse;
	BRDFGlossySpecular*specular;

	void setAmbient(float i,RGBColor c);
	void setDiffuse(float i,RGBColor c);
	void setSpecular(float i,RGBColor c,float exp);
};

#endif /* MATERIALPHONG_H_ */
