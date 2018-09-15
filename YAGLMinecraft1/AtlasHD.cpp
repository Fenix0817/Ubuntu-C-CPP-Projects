/*
 * AtlasHD.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#include "AtlasHD.h"

AtlasHD::AtlasHD() {
	// TODO Auto-generated constructor stub

}

AtlasHD::~AtlasHD() {
	// TODO Auto-generated destructor stub
}


std::string AtlasHD::getFileName(){
	return "HopsonCraftAtlas/old/HD.png";
}

TexturePos AtlasHD::getTexturePos(AtlasPos ap){
	if(ap==AtlasPos::GrassTop)return TexturePos(0,15,16,16);
	if(ap==AtlasPos::GrassSide)return TexturePos(1,15,16,16);
	if(ap==AtlasPos::Dirt)return TexturePos(2,15,16,16);
	if(ap==AtlasPos::Stone)return TexturePos(3,15,16,16);
	if(ap==AtlasPos::Sand)return TexturePos(4,15,16,16);
	if(ap==AtlasPos::WoodSide)return TexturePos(5,15,16,16);
	if(ap==AtlasPos::WoodTop)return TexturePos(6,15,16,16);
	if(ap==AtlasPos::Leaf)return TexturePos(7,15,16,16);
	if(ap==AtlasPos::Water)return TexturePos(8,15,16,16);
	if(ap==AtlasPos::Snow)return TexturePos(9,15,16,16);
	return TexturePos(0,0,1,1);
}
