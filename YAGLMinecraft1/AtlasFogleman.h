/*
 * AtlasFogleman.h
 *
 *  Created on: Sep 21, 2018
 *      Author: jack
 */

#ifndef ATLASFOGLEMAN_H_
#define ATLASFOGLEMAN_H_

#include "Atlas.h"

class AtlasFogleman : public Atlas {
public:
	AtlasFogleman();
	virtual ~AtlasFogleman();

	std::string getFileName();
	TexturePos getTexturePos(AtlasPos ap);
};

#endif /* ATLASFOGLEMAN_H_ */
