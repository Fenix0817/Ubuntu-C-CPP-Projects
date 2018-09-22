/*
 * Chunk.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#include "Chunk.h"

Chunk::Chunk() {
	// TODO Auto-generated constructor stub
}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}


Chunk::Chunk(int x,int z){
	chunkPos=glm::vec2i(x,z);
}

Chunk* emptyChunk(){
	Chunk* c=new Chunk();
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int y=0;y<CHUNK_HEIGHT;y++){
			for(int z=0;z<CHUNK_SIZE;z++){
				c->blockData[x][y][z]=blockEmpty;
			}
		}
	}
	return c;
}

void Chunk::addTriangle(unsigned int a,unsigned int b,unsigned int c){
	unsigned int i=posData.size()/3;
	triData.push_back(i+a);
	triData.push_back(i+b);
	triData.push_back(i+c);
}

void Chunk::addPos(float x,float y,float z){
	posData.push_back(x);
	posData.push_back(16-y);
	posData.push_back(z);
}

void Chunk::addUV(float u,float v){
	uvData.push_back(u);
	uvData.push_back(v);
}

void Chunk::addUV(glm::vec2 v){
	addUV(v.x,v.y);
}

void Chunk::addUV(TexturePos tp,bool flip){
	addUV(tp._00);
	if(flip){
		addUV(tp._10);
		addUV(tp._01);
	}else{
		addUV(tp._01);
		addUV(tp._10);
	}
	addUV(tp._11);
}

void Chunk::addTriangleFace(){
	addTriangle(0,1,2);
	addTriangle(1,2,3);
}

bool Chunk::isEmpty(int x,int y,int z){
	if(
//			x<0||x>=CHUNK_SIZE||
			y<0||y>=CHUNK_HEIGHT
//			||z<0||z>=CHUNK_SIZE
			)return true;
	if(x<0)return cXMI->isEmptyReal(x+CHUNK_SIZE,y,z);
	if(x>=CHUNK_SIZE)return cXPL->isEmptyReal(x-CHUNK_SIZE,y,z);
	if(z<0)return cZMI->isEmptyReal(x,y,z+CHUNK_SIZE);
	if(z>=CHUNK_SIZE)return cZPL->isEmptyReal(x,y,z-CHUNK_SIZE);
//	if(y<0||y>=CHUNK_HEIGHT)return true;
	return isEmptyReal(x,y,z);
}

bool Chunk::isEmptyReal(int x,int y,int z){
	return blockData[x][y][z].empty;
}

void Chunk::createChunkData(FastNoise*fn){
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int z=0;z<CHUNK_SIZE;z++){

//			int h=x;
			float zoom=1;
			fn->SetFractalOctaves(10);
			fn->SetFractalLacunarity(2);
			fn->SetFractalType(FastNoise::FBM);
			float fh=CHUNK_HEIGHT/2+30*fn->GetSimplexFractal( zoom*(chunkPos.x*CHUNK_SIZE+x),zoom*(chunkPos.y*CHUNK_SIZE+z));
			int h=(int)fh;
//			int h=chunkPos.x*chunkPos.y;
			for(int y=0;y<CHUNK_HEIGHT;y++){
//				if(y==h)blockData[x][y][z]=blockGrass;
//				else blockData[x][y][z]=blockEmpty;
				if(y<h-10)blockData[x][y][z]=blockStone;
				else if(y<h)blockData[x][y][z]=blockDirt;
				else if(y==h){
					blockData[x][y][z]=blockGrass;
//					int r=rand()%5;
//					if(r==0)chunk[x][y][z]=blockGrass;
//					if(r==1)blockData[x][y][z]=blockDirt;
//					if(r==2)blockData[x][y][z]=blockStone;
//					if(r==3)blockData[x][y][z]=blockSand;
//					if(r==4)blockData[x][y][z]=blockSnow;
				}
				else blockData[x][y][z]=blockEmpty;
			}

		}
	}
}

void Chunk::prepareMesh(Atlas*atlas){
//	this->cXMI=xmi;
//	this->cXPL=xpl;
//	this->cZMI=zpl;
//	this->cZPL=zpl;
	posData.clear();
	uvData.clear();
	triData.clear();
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int y=0;y<CHUNK_HEIGHT;y++){
			for(int z=0;z<CHUNK_SIZE;z++){

				Block b=blockData[x][y][z];

				if(b.empty)continue;

				TexturePos xmiTP=atlas->getTexturePos(b.xmi);
				TexturePos xplTP=atlas->getTexturePos(b.xpl);
				TexturePos ymiTP=atlas->getTexturePos(b.ymi);
				TexturePos yplTP=atlas->getTexturePos(b.ypl);
				TexturePos zmiTP=atlas->getTexturePos(b.zmi);
				TexturePos zplTP=atlas->getTexturePos(b.zpl);

				if(isEmpty(x-1,y,z)){//xmi
					addTriangleFace();
					addPos(x,y,z);
					addPos(x,y+1,z);
					addPos(x,y,z+1);
					addPos(x,y+1,z+1);
					addUV(xmiTP);
				}

				if(isEmpty(x+1,y,z)){//xpl
					addTriangleFace();
					addPos(x+1,y,z);
					addPos(x+1,y+1,z);
					addPos(x+1,y,z+1);
					addPos(x+1,y+1,z+1);
					addUV(xplTP);
				}

				if(isEmpty(x,y-1,z)){//ymi
					addTriangleFace();
					addPos(x,y,z);
					addPos(x+1,y,z);
					addPos(x,y,z+1);
					addPos(x+1,y,z+1);
					addUV(ymiTP);
				}

				if(isEmpty(x,y+1,z)){//ypl
					addTriangleFace();
					addPos(x,y+1,z);
					addPos(x+1,y+1,z);
					addPos(x,y+1,z+1);
					addPos(x+1,y+1,z+1);
					addUV(yplTP);
				}

				if(isEmpty(x,y,z-1)){//zmi
					addTriangleFace();
					addPos(x,y,z);
					addPos(x,y+1,z);
					addPos(x+1,y,z);
					addPos(x+1,y+1,z);
					addUV(zmiTP);
				}

				if(isEmpty(x,y,z+1)){//zpl
					addTriangleFace();
					addPos(x,y,z+1);
					addPos(x,y+1,z+1);
					addPos(x+1,y,z+1);
					addPos(x+1,y+1,z+1);
					addUV(zplTP);
				}

			}
		}
	}
//	printf("%i,%i,%i\n",posData.size(),uvData.size(),triData.size());
}

void Chunk::prepareGL(){
	vao.create();
	vao.bind();

	vboPos=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(float)*posData.size(),posData.data());
	vboPos.addVertexAttrib(0,3,false,3,0);
	vboPos.unbind();

	vboUV=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(float)*uvData.size(),uvData.data());
	vboUV.addVertexAttrib(1,2,false,2,0);
	vboUV.unbind();

	ebo=gl::VertexBuffer(gl::VertexBufferTarget::ElementArray,gl::VertexBufferUsage::StaticDraw,gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(unsigned int)*triData.size(),triData.data());
	ebo.unbind();

	vao.unbind();

}

glm::mat4 Chunk::getModelMatrix(){
	return glm::translate(glm::mat4(1),glm::vec3(CHUNK_SIZE*chunkPos.x,0,CHUNK_SIZE*chunkPos.y));
}
void Chunk::render(){
//	printf("%i,%i,%i,%i\n",vao.id,vboPos.id,vboUV.id,ebo.id);
	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
}
