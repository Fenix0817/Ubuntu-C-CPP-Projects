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
struct Intersection{
	glm::ivec2 chunk;
	glm::ivec3 pos;
	bool hit;
	glm::ivec3 absPos(){
		return pos+glm::ivec3(chunk.x,0,chunk.y)*CHUNK_SIZE;
	}
	Intersection(glm::ivec3 p){
		hit=true;
		glm::ivec2 chunkCoord=getChunkCoord(glm::ivec2(p.x,p.z));
		glm::ivec2 posInChunk=getPosInChunk(glm::ivec2(p.x,p.z));
		chunk=chunkCoord;
		pos=glm::ivec3(posInChunk.x,p.y,posInChunk.y);
	}
	Intersection(bool b){
		hit=b;
	}
};

template<typename T>inline int sign(T x){
	return (T(0)<x)-(x<T(0));
}

//inline float intbound(float s,float ds){
//	if(ds<0){
//		return intbound(-s,-ds);
//	}else{
//		s=fmod(s,1);
//		return (1-s)/ds;
//	}
//}

inline float intbound(float s,float ds){
	return (ds > 0? ceil(s)-s: s-floor(s)) / fabs(ds);
}

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

	//In world coordinates, not pos in chunk coordinates
	Intersection intersectWorld(glm::vec3 start,glm::vec3 dir,int range);

private:
	void eraseChunk(int x,int z);
	ChunkPtr getChunk(int x,int z,bool instantiate);

};

#endif /* CHUNKMANAGER_H_ */
