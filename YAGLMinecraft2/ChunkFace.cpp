/*
 * ChunkFace.cpp
 *
 *  Created on: Nov 19, 2018
 *      Author: jack
 */

#include "ChunkFace.h"

ChunkFace::ChunkFace() {
	// TODO Auto-generated constructor stub

}

ChunkFace::~ChunkFace() {
	// TODO Auto-generated destructor stub
}

void ChunkFace::init(int num){
	vboVis=ChunkUtils::createStaticArrayIntBuffer();
	vboVis.bind();
	vboVis.addVertexAttrib(num,1,false,1,(const GLvoid*)0);
	vboVis.unbind();
	vboUV=ChunkUtils::createStaticArrayFloatBuffer();
	vboUV.bind();
	vboUV.addVertexAttrib(num+6,1,false,1,(const GLvoid*)0);
}

void ChunkFace::setVis(int x,int y,int z,bool b){
	visData[x][y][z]=b;
}
void ChunkFace::setUV(int x,int y,int z,float u,float v){
	uvData[x][y][z][0]=u;
	uvData[x][y][z][1]=v;
}

void ChunkFace::updateVisBuffer(){
	vboVis.bind();
	vboVis.setData(sizeof(visData),visData);
	vboVis.unbind();
}

void ChunkFace::updateUVBuffer(){
	vboUV.bind();
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.unbind();
}

void ChunkFace::updateBuffers(){
	updateVisBuffer();
	updateUVBuffer();
}
