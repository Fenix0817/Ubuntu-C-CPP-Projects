/*
 * AtlasMCSimple.h
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#ifndef ATLASMCSIMPLE_H_
#define ATLASMCSIMPLE_H_

#include "Atlas.h"

class AtlasMCSimple : public Atlas {
public:
	AtlasMCSimple();
	virtual ~AtlasMCSimple();

	std::string getFileName();
	TexturePos getTexturePos(AtlasPos ap);
};

#endif /* ATLASMCSIMPLE_H_ */
