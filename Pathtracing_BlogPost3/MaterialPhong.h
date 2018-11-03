/*
 * MaterialPhong.h
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#ifndef MATERIALPHONG_H_
#define MATERIALPHONG_H_

#include "Material.h"
#include "BRDF.h"
#include "BRDFLambertian.h"
#include "BRDFGlossySpecular.h"
#include "Light.h"
#include "World.h"

class MaterialPhong : public Material {
public:
	inline MaterialPhong(){
		ambient=new BRDFLambertian();
		diffuse=new BRDFLambertian();
		specular=new BRDFGlossySpecular();
	}
	virtual ~MaterialPhong();

	inline void setAmbient(float i,RGBColor c){
		ambient->intensity=i;
		ambient->color=c;
	}

	inline void setDiffuse(float i,RGBColor c){
		diffuse->intensity=i;
		diffuse->color=c;
	}

	inline void setSpecular(float i,RGBColor c,float e){
		specular->intensity=i;
		specular->color=c;
		specular->exp=e;
	}

	RGBColor shade(ShadeInfo&si);
	RGBColor giShade(ShadeInfo&si);

	BRDFLambertian*ambient;
	BRDFLambertian*diffuse;
	BRDFGlossySpecular*specular;
};

#endif /* MATERIALPHONG_H_ */
