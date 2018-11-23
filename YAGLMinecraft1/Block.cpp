/*
 * Block.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */

#include "Block.h"

Block::Block() {
	// TODO Auto-generated constructor stub
	name="no name";
}

Block::Block(std::string n,bool empty){
	this->empty=empty;
	name=n;
}

Block::Block(std::string n,AtlasPos xmi,AtlasPos xpl,AtlasPos ymi,AtlasPos ypl,AtlasPos zmi,AtlasPos zpl){
	this->xmi=xmi;
	this->xpl=xpl;
	this->ymi=ymi;
	this->ypl=ypl;
	this->zmi=zmi;
	this->zpl=zpl;
	name=n;
}

Block::Block(std::string n,AtlasPos top,AtlasPos side,AtlasPos bot){
	xmi=side;
	xpl=side;
	ymi=bot;
	ypl=top;
	zmi=side;
	zpl=side;
	name=n;
}

Block::Block(std::string n,AtlasPos p){
	xmi=xpl=ymi=ypl=zmi=zpl=p;
	name=n;
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

