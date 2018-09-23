/*
 * AtlasFogleman.cpp
 *
 *  Created on: Sep 21, 2018
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

TexturePos AtlasFogleman::getTexturePos(AtlasPos ap){
	if(ap==AtlasPos::GrassTop)return TexturePos(0,2,16,16);
	if(ap==AtlasPos::GrassSide)return TexturePos(0,1,16,16);
	if(ap==AtlasPos::Dirt)return TexturePos(0,0,16,16);
	if(ap==AtlasPos::Stone)return TexturePos(5,0,16,16);
	if(ap==AtlasPos::Sand)return TexturePos(1,0,16,16);
	if(ap==AtlasPos::WoodSide)return TexturePos(4,1,16,16);
	if(ap==AtlasPos::WoodTop)return TexturePos(4,2,16,16);
	if(ap==AtlasPos::Leaf)return TexturePos(14,0,16,16);
	if(ap==AtlasPos::Water)return TexturePos(9,11,16,16);
	if(ap==AtlasPos::Snow)return TexturePos(8,2,16,16);
	return TexturePos(0,0,1,1);
}
