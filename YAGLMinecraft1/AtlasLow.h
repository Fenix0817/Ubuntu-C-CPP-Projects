/*
 * AtlasLow.h
 *
 *  Created on: Sep 15, 2018
 *      Author: jack
 */

#ifndef ATLASLOW_H_
#define ATLASLOW_H_

#include "Atlas.h"

class AtlasLow : public Atlas {
public:
	AtlasLow();
	virtual ~AtlasLow();

	std::string getFileName();
	TexturePos getTexturePos(AtlasPos ap);
};

#endif /* ATLASLOW_H_ */
