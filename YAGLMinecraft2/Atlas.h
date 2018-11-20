/*
 * Atlas.h
 *
 *  Created on: Nov 3, 2018
 *      Author: jack
 */

#ifndef ATLAS_H_
#define ATLAS_H_

#include <string>
#include "Texture.h"
#include "AtlasPos.h"
#include "BlockFace.h"

class Atlas {
public:
	Atlas();
	virtual ~Atlas();

	virtual std::string getFileName()=0;
	virtual AtlasPos getAtlasPos(BlockFace face)=0;
};

#endif /* ATLAS_H_ */
