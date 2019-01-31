/*
 * ChunkManager.h
 *
 *  Created on: Sep 23, 2018
 *      Author: jack
 */

#ifndef CHUNKMANAGER_H_
#define CHUNKMANAGER_H_

#include "Chunk.h"
#include "Atlas.h"
#include <vector>
#include "utils.h"
#include "Shader.h"
#include <algorithm>

bool contains_ivec2(std::vector<glm::ivec2>list,glm::ivec2 v);
bool contains_ivec3(std::vector<glm::ivec3>list,glm::ivec3 v);

struct Intersection{
	glm::ivec3 abs;
	glm::ivec3 prev;
	glm::vec3 normal;
	bool hit;
	float dist;
//	glm::ivec2 chunkCoord(){
//		glm::ivec2 pos(abs.x,abs.z);
//		return getChunkCoord(pos);
//	}
	glm::ivec3 posInChunk(){
		glm::ivec2 pos(abs.x,abs.z);
		glm::ivec2 pInChunk=getPosInChunk(pos);
		return glm::ivec3(pInChunk.x,abs.y,pInChunk.y);
	}
	glm::ivec3 absPos(){
		return abs;
	}
	Intersection(glm::ivec3 p,glm::ivec3 prev,glm::vec3 n){
		hit=true;
		abs=p;
		normal=n;
		this->prev=prev;
	}
	Intersection(bool b){
		hit=b;
	}
};

template<typename T>inline int sign(T x){
	return (T(0)<x)-(x<T(0));
}

//struct LightChangeWithChunk{
//	glm::ivec3 p;
//	glm::ivec2 c;
//};

class ChunkManager {
public:
	ChunkManager();
	virtual ~ChunkManager();

	std::vector<glm::ivec2> chunksToAdd;
	std::vector<glm::ivec2> chunksToRemove;

	std::vector<ChunkPtr> chunks;

	FastNoisePtr noise;
	AtlasPtr atlas;

	void render(gl::Shader shader,glm::mat4 vp);
	void update(int frames,glm::ivec2 chunkPos);

	void setBlock(int x,int y,int z,Block b);
	void remeshChunk(int x,int z);

	Block getBlock(int x,int y,int z);
	Block getBlock(glm::ivec3 p);

	int getNumChunksInMemory();
	int getNumChunksRendered();

	float getLight(int x,int y,int z);

	//In world coordinates, not pos in chunk coordinates
	Intersection intersectWorld(glm::vec3 start,glm::vec3 dir,float range);

private:
	void eraseChunk(int x,int z);
	ChunkPtr getChunk(int x,int z,bool instantiate);

};

#endif /* CHUNKMANAGER_H_ */
