/*
 * ShadeInfo.h
 *
 *  Created on: Sep 28, 2018
 *      Author: jack
 */

#ifndef SHADEINFO_H_
#define SHADEINFO_H_

#include "utils.h"

struct ShadeInfo {
	Normal normal;
	float t;
	bool hit;
};

#endif /* SHADEINFO_H_ */
