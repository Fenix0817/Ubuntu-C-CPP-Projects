/*
 * MaterialReflective.h
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#ifndef MATERIALREFLECTIVE_H_
#define MATERIALREFLECTIVE_H_

#include "MaterialPhong.h"
#include "BRDFPerfectSpecular.h"
#include "Tracer.h"

class MaterialReflective : public MaterialPhong {
public:
	MaterialReflective(){
		reflective=new BRDFPerfectSpecular();
	}
	virtual ~MaterialReflective();

	void setReflective(float i,RGBColor c){
		reflective->intensity=i;
		reflective->color=c;
	}

	RGBColor shade(ShadeInfo&si);
	RGBColor giShade(ShadeInfo&si);

	BRDFPerfectSpecular*reflective;
};

#endif /* MATERIALREFLECTIVE_H_ */
