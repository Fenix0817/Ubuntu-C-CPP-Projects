/*
 * MaterialUnshaded.h
 *
 *  Created on: Oct 11, 2018
 *      Author: jack
 */

#ifndef MATERIALUNSHADED_H_
#define MATERIALUNSHADED_H_

#include "Material.h"
#include "Colors.h"
#include "ShadeInfo.h"
#include "World.h"

class MaterialUnshaded : public Material {
public:
	MaterialUnshaded();
	virtual ~MaterialUnshaded();

	RGBColor shade(ShadeInfo&si);

	RGBColor color;

	bool ambient=false;

	void setColor(RGBColor c);
	void setAmbient(bool a);
};

#endif /* MATERIALUNSHADED_H_ */
