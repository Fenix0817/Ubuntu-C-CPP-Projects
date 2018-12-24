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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Chunk {
public:
	Chunk();
	virtual ~Chunk();

	inline Chunk(int x,int y){
		pos=glm::ivec2(x,y);
	}

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;

	ChunkFace xmi,xpl,ymi,ypl,zmi,zpl;

	glm::ivec2 pos;

	float posData[C_SIZE][C_HEIGHT][C_SIZE][3];

	Block blockData[C_SIZE][C_HEIGHT][C_SIZE];

	glm::mat4 getModelMatrix();

	void createBuffers();
	void updateBuffers(Atlas*atlas,Chunk*cxmi,Chunk*cxpl,Chunk*czmi,Chunk*czpl);

	void render();

	void setBlock(int x,int y,int z,Block block);

private:
	bool dirtyBlocks[C_SIZE][C_HEIGHT][C_SIZE];
};

#endif /* CHUNK_H_ */
