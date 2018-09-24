/*
 * Chunk.h
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#ifndef CHUNK_H_
#define CHUNK_H_

#include "utils.h"
#include "Block.h"
#include "TexturePos.h"
#include "Atlas.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"

#include "FastNoise.h"

#include <vector>

const int CHUNK_SIZE=16;
const int CHUNK_HEIGHT=50;

class Chunk;

typedef Chunk* ChunkPtr;

class Chunk {
private:
	std::vector<float>posData;
	std::vector<float>uvData;
	std::vector<unsigned int>triData;

	void addTriangle(unsigned int a,unsigned int b,unsigned int c);
	void addPos(float x,float y,float z);
	void addUV(float u,float v);
	void addUV(glm::vec2 v);
	void addUV(TexturePos tp,bool flip=false);
	void addTriangleFace();

public:
	bool isEmpty(int x,int y,int z);

	Chunk();
	virtual ~Chunk();

	Chunk(int x,int z);

	glm::vec2i chunkPos;

	Chunk *cXMI;
	Chunk *cXPL;
	Chunk *cZMI;
	Chunk *cZPL;

	Block blockData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboUV;
	gl::VertexBuffer ebo;

	bool instantiated=false;
	bool meshCreated=false;

	void createChunkData(FastNoise*fn);
	void prepareMesh(Atlas*atlas);
	void prepareGL();

	bool isEmptyReal(int x,int y,int z);

	glm::mat4 getModelMatrix();
	void render();
};

Chunk* emptyChunk();

#endif /* CHUNK_H_ */
