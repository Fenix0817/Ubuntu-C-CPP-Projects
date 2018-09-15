/*
 * Block.h
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "AtlasPos.h"

class Block {
public:

	AtlasPos xmi,xpl,ymi,ypl,zmi,zpl;
	bool empty=false;

	Block();
	Block(bool empty);
	Block(AtlasPos xmi,AtlasPos xpl,AtlasPos ymi,AtlasPos ypl,AtlasPos zmi,AtlasPos zpl);
	Block(AtlasPos top,AtlasPos side,AtlasPos bot);
	Block(AtlasPos p);
	virtual ~Block();
};

const Block blockEmpty(true);
const Block blockGrass(AtlasPos::GrassTop,AtlasPos::GrassSide,AtlasPos::Dirt);
const Block blockDirt(AtlasPos::Dirt);
const Block blockStone(AtlasPos::Stone);
const Block blockSand(AtlasPos::Sand);
const Block blockWood(AtlasPos::WoodTop,AtlasPos::WoodSide,AtlasPos::WoodTop);
const Block blockLeaf(AtlasPos::Leaf);
const Block blockWater(AtlasPos::Water);
const Block blockSnow(AtlasPos::Snow);

#endif /* BLOCK_H_ */
