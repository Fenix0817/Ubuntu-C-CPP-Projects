/*
 * Block.h
 *
 *  Created on: Nov 3, 2018
 *      Author: jack
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "BlockFace.h"

struct Block{
	bool empty=false;
	BlockFace xmi,xpl,ymi,ypl,zmi,zpl;
	Block(BlockFace a,BlockFace b,BlockFace c,BlockFace d,BlockFace e,BlockFace f){
		xmi=a;
		xpl=b;
		ymi=c;
		ypl=d;
		zmi=e;
		zpl=f;
	}
	Block(BlockFace a){
		xmi=xpl=ymi=ypl=zmi=zpl=a;
	}
	Block(BlockFace top,BlockFace side,BlockFace bot){
		xmi=xpl=zmi=zpl=side;
		ypl=top;
		ymi=bot;
	}
	Block(){
		empty=true;
	}
};

const Block blockGrass(GrassTop,GrassSide,Dirt);
const Block blockDirt(Dirt);
const Block blockStone(Stone);
const Block blockEmpty;

#endif /* BLOCK_H_ */
