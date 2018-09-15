/*
 * Atlas.h
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#ifndef ATLAS_H_
#define ATLAS_H_

#include "AtlasPos.h"
#include "TexturePos.h"
#include <string>

class Atlas {
public:
	Atlas();
	virtual ~Atlas();

	virtual std::string getFileName()=0;
	virtual TexturePos getTexturePos(AtlasPos ap)=0;
};

#endif /* ATLAS_H_ */
