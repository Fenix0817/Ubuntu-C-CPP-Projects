/*
 * Chunk.h
 *
 *  Created on: Nov 3, 2018
 *      Author: jack
 */

#ifndef CHUNK_H_
#define CHUNK_H_

#include "VertexArray.h"
#include "VertexBuffer.h"

#include "ChunkUtils.h"
#include "ChunkFace.h"

#include "Atlas.h"
#include "AtlasPos.h"
#include "Block.h"
#include "BlockFace.h"
#include "config.h"

class Chunk {
public:
	Chunk();
	virtual ~Chunk();

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;

	ChunkFace xmi,xpl,ymi,ypl,zmi,zpl;

	float posData[C_SIZE][C_HEIGHT][C_SIZE][3];

	Block blockData[C_SIZE][C_HEIGHT][C_SIZE];

	void createBuffers();
	void updateBuffers(Atlas*atlas);

	void render();

	void setBlock(int x,int y,int z,Block block);

private:
	bool dirtyBlocks[C_SIZE][C_HEIGHT][C_SIZE];
};

#endif /* CHUNK_H_ */
