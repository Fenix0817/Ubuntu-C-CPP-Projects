/*
 * AtlasFogleman.cpp
 *
 *  Created on: Nov 19, 2018
 *      Author: jack
 */

#include "AtlasFogleman.h"

AtlasFogleman::AtlasFogleman() {
	// TODO Auto-generated constructor stub

}

AtlasFogleman::~AtlasFogleman() {
	// TODO Auto-generated destructor stub
}

std::string AtlasFogleman::getFileName(){
	return "FoglemanAtlas/fogleman.png";
}
AtlasPos AtlasFogleman::getAtlasPos(BlockFace face){
	if(face==GrassTop)return AtlasPos(0,2, 1,1, 16,16);
	if(face==GrassSide)return AtlasPos(0,1, 1,1, 16,16);
	if(face==Dirt)return AtlasPos(0,0, 1,1, 16,16);
	if(face==Stone)return AtlasPos(5,0, 1,1, 16,16);
	return AtlasPos(0,0, 1,1, 1,1);
}

