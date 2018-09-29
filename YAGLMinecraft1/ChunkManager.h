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

bool contains_ivec2(std::vector<glm::ivec2>list,glm::ivec2 v);

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

private:
	void eraseChunk(int x,int z);
	ChunkPtr getChunk(int x,int z,bool instantiate);

};

#endif /* CHUNKMANAGER_H_ */