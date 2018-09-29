/*
 * ChunkManager.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: jack
 */

#include "ChunkManager.h"

ChunkManager::ChunkManager() {
	// TODO Auto-generated constructor stub

}

ChunkManager::~ChunkManager() {
	// TODO Auto-generated destructor stub
}

bool contains_ivec2(std::vector<glm::ivec2> list,glm::ivec2 v){
	for(int i=0;i<list.size();i++)if(list[i]==v)return true;
	return false;
}

ChunkPtr ChunkManager::getChunk(int x,int z,bool instantiateChunk){
	bool foundChunk=false;
	ChunkPtr c=nullptr;
	for(int i=0;i<chunks.size()&&!foundChunk;i++){
		if(chunks[i]->chunkPos.x==x&&chunks[i]->chunkPos.y==z){
			c=chunks[i];
			foundChunk=true;
		}
	}
	if(!foundChunk){
#ifdef DEBUG_CHUNKMANAGER
		printf("\tCreating data for %i,%i\n",x,z);
#endif
		c=new Chunk();
		c->chunkPos=glm::ivec2(x,z);
		c->createChunkData(noise);
		chunks.push_back(c);
#ifdef DEBUG_CHUNKMANAGER
		printf("\tFinished creating data for %i,%i\n",x,z);
#endif
	}
	if(instantiateChunk){
		c->instantiated=true;
	}
	if(instantiateChunk&&!c->meshCreated){
#ifdef DEBUG_CHUNKMANAGER
		printf("\nInstantiating %i,%i\n",x,z);
#endif
		c->meshCreated=true;
		ChunkPtr xmi=getChunk(x-1,z,false);
		ChunkPtr xpl=getChunk(x+1,z,false);
		ChunkPtr zmi=getChunk(x,z-1,false);
		ChunkPtr zpl=getChunk(x,z+1,false);
		c->cXMI=xmi;
		c->cXPL=xpl;
		c->cZMI=zmi;
		c->cZPL=zpl;
		c->prepareMesh(atlas);
		c->prepareGL();
#ifdef DEBUG_CHUNKMANAGER
		printf("Finished instantiating %i,%i:  %i,%i,%i,%i\n",x,z,c->vao.id,c->vboPos.id,c->vboUV.id,c->ebo.id);
#endif
	}
	return c;
}

void ChunkManager::eraseChunk(int x,int z){
	for(int i=0;i<chunks.size();i++){
		if(chunks[i]->chunkPos==glm::ivec2(x,z)){
			chunks[i]->instantiated=false;
		}
	}
}

void ChunkManager::setBlock(int x,int y,int z,Block b){
	glm::ivec2 xz(x,z);
	glm::ivec2 chunkCoord=getChunkCoord(xz);
	glm::ivec2 pos=getPosInChunk(xz);
	ChunkPtr chunk=getChunk(chunkCoord.x,chunkCoord.y,false);
	chunk->blockData[pos.x][y][pos.y]=b;
}

void ChunkManager::remeshChunk(int x,int z){
	ChunkPtr chunk=getChunk(x,z,false);
	ChunkPtr xmi=getChunk(x-1,z,false);
	ChunkPtr xpl=getChunk(x+1,z,false);
	ChunkPtr zmi=getChunk(x,z-1,false);
	ChunkPtr zpl=getChunk(x,z+1,false);
	chunk->cXMI=xmi;
	chunk->cXPL=xpl;
	chunk->cZMI=zmi;
	chunk->cZPL=zpl;
	chunk->prepareMesh(atlas);
	chunk->prepareGL();
}


void ChunkManager::render(gl::Shader shader,glm::mat4 vp){
	for(unsigned int i=0;i<chunks.size();i++){
		ChunkPtr c=chunks[i];
		if(c->instantiated){
			shader.setMat4("MVP",vp*c->getModelMatrix());
			c->render();
		}
	}
}

void ChunkManager::update(int frames,glm::ivec2 chunkPos){
	int chunkX=chunkPos.x;
	int chunkZ=chunkPos.y;

	int o=10;
	for(int x=-o;x<=o;x++){
		for(int z=-o;z<=o;z++){
			if(!contains_ivec2(chunksToAdd,glm::ivec2(x+chunkX,z+chunkZ))){
				chunksToAdd.push_back(glm::ivec2(x+chunkX,z+chunkZ));
			}
//				getChunk(x+chunkX,z+chunkZ,true);
		}
	}
	for(int i=0;i<10;i++){
	if(frames%1==0&&chunksToAdd.size()>0){
		glm::ivec2 chunkToAdd=chunksToAdd[0];
		getChunk(chunkToAdd.x,chunkToAdd.y,true);
		chunksToAdd.erase(chunksToAdd.begin());
	}}
	for(int i=0;i<200;i++){
	if(frames%1==0&&chunksToRemove.size()>0){
		glm::ivec2 chunkToRem=chunksToRemove[0];
		eraseChunk(chunkToRem.x,chunkToRem.y);
		chunksToRemove.erase(chunksToRemove.begin());
	}}

	for(int i=0;i<chunks.size();i++){
		float d=max(abs(chunks[i]->chunkPos.x-chunkX),abs(chunks[i]->chunkPos.y-chunkZ));
		if(d>o+2&&!contains_ivec2(chunksToRemove,chunks[i]->chunkPos))chunksToRemove.push_back(chunks[i]->chunkPos);
	}
}
