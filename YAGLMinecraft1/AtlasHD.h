/*
 * AtlasHD.h
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#ifndef ATLASHD_H_
#define ATLASHD_H_

#include "Atlas.h"

class AtlasHD : public Atlas {
public:
	AtlasHD();
	virtual ~AtlasHD();

	std::string getFileName();
	TexturePos getTexturePos(AtlasPos ap);
};

#endif /* ATLASHD_H_ */
