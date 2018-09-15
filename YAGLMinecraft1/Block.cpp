/*
 * Block.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#include "Block.h"

Block::Block() {
	// TODO Auto-generated constructor stub

}

Block::Block(bool empty){
	this->empty=empty;
}

Block::Block(AtlasPos xmi,AtlasPos xpl,AtlasPos ymi,AtlasPos ypl,AtlasPos zmi,AtlasPos zpl){
	this->xmi=xmi;
	this->xpl=xpl;
	this->ymi=ymi;
	this->ypl=ypl;
	this->zmi=zmi;
	this->zpl=zpl;
}

Block::Block(AtlasPos top,AtlasPos side,AtlasPos bot){
	xmi=side;
	xpl=side;
	ymi=bot;
	ypl=top;
	zmi=side;
	zpl=side;
}

Block::Block(AtlasPos p){
	xmi=xpl=ymi=ypl=zmi=zpl=p;
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

