/*
 * Material.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Math.h"
#include "ShadeInfo.h"
#include "Light.h"

class Material {
public:
	Material();
	virtual ~Material();

	virtual RGBColor shade(ShadeInfo&si)=0;
};

#endif /* MATERIAL_H_ */
