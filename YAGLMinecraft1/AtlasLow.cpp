/*
 * AtlasLow.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: jack
 */

#include "AtlasLow.h"

AtlasLow::AtlasLow() {
	// TODO Auto-generated constructor stub

}

AtlasLow::~AtlasLow() {
	// TODO Auto-generated destructor stub
}

std::string AtlasLow::getFileName(){
	return "HopsonCraftAtlas/Low.png";
}

TexturePos AtlasLow::getTexturePos(AtlasPos ap){
	if(ap==AtlasPos::GrassTop )return TexturePos( 0,31,32,32);
	if(ap==AtlasPos::GrassSide)return TexturePos( 1,31,32,32);
	if(ap==AtlasPos::Dirt     )return TexturePos( 2,31,32,32);
	if(ap==AtlasPos::Stone    )return TexturePos( 3,31,32,32);
	if(ap==AtlasPos::Sand     )return TexturePos( 4,31,32,32);
	if(ap==AtlasPos::WoodSide )return TexturePos( 5,31,32,32);
	if(ap==AtlasPos::WoodTop  )return TexturePos( 6,31,32,32);
	if(ap==AtlasPos::Leaf     )return TexturePos( 7,31,32,32);
	if(ap==AtlasPos::Water    )return TexturePos( 8,31,32,32);
	if(ap==AtlasPos::Snow     )return TexturePos( 9,31,32,32);
	return TexturePos(0,0,1,1);
}
