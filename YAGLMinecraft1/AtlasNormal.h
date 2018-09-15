/*
 * AtlasNormal.h
 *
 *  Created on: Sep 15, 2018
 *      Author: jack
 */

#ifndef ATLASNORMAL_H_
#define ATLASNORMAL_H_

#include "Atlas.h"

class AtlasNormal : public Atlas {
public:
	AtlasNormal();
	virtual ~AtlasNormal();

	std::string getFileName();
	TexturePos getTexturePos(AtlasPos ap);
};

#endif /* ATLASNORMAL_H_ */
