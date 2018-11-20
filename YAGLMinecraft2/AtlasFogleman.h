/*
 * AtlasFogleman.h
 *
 *  Created on: Nov 19, 2018
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
	AtlasPos getAtlasPos(BlockFace face);
};

#endif /* ATLASFOGLEMAN_H_ */
