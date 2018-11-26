/*
 * Block.h
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "AtlasPos.h"
#include <string>

class Block {
public:

	AtlasPos xmi,xpl,ymi,ypl,zmi,zpl;
	bool empty=false;
//	std::string name="";

	Block();
	Block(std::string name,bool empty);
	Block(std::string name,AtlasPos xmi,AtlasPos xpl,AtlasPos ymi,AtlasPos ypl,AtlasPos zmi,AtlasPos zpl);
	Block(std::string name,AtlasPos top,AtlasPos side,AtlasPos bot);
	Block(std::string name,AtlasPos p);
	virtual ~Block();
};

const Block blockEmpty("empty",true);
const Block blockGrass("grass",AtlasPos::GrassTop,AtlasPos::GrassSide,AtlasPos::Dirt);
const Block blockDirt("dirt",AtlasPos::Dirt);
const Block blockStone("stone",AtlasPos::Stone);
const Block blockSand("sand",AtlasPos::Sand);
const Block blockWood("wood",AtlasPos::WoodTop,AtlasPos::WoodSide,AtlasPos::WoodTop);
const Block blockLeaf("leaf",AtlasPos::Leaf);
const Block blockWater("water",AtlasPos::Water);
const Block blockSnow("snow",AtlasPos::Snow);

#endif /* BLOCK_H_ */
