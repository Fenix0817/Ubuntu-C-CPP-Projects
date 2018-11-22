/*
 * AtlasMCSimple.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#include "AtlasMCSimple.h"

AtlasMCSimple::AtlasMCSimple() {
	// TODO Auto-generated constructor stub

}

AtlasMCSimple::~AtlasMCSimple() {
	// TODO Auto-generated destructor stub
}

std::string AtlasMCSimple::getFileName(){
	return "MCAtlas/simple.png";
}
TexturePos AtlasMCSimple::getTexturePos(AtlasPos ap){
	if(ap==AtlasPos::GrassTop)return TexturePos(0,15, 16,16);
	if(ap==AtlasPos::GrassSide)return TexturePos(3,15, 16,16);
	if(ap==AtlasPos::Dirt)return TexturePos(2,15, 16,16);
	if(ap==AtlasPos::Stone)return TexturePos(1,15, 16,16);
	if(ap==AtlasPos::Sand)return TexturePos(2,14, 16,16);
	if(ap==AtlasPos::Snow)return TexturePos(0,11, 16,16);
	return TexturePos(0,0, 1,1);
}
