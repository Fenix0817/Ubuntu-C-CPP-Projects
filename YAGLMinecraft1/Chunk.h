/*
 * Chunk.h
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#ifndef CHUNK_H_
#define CHUNK_H_

#include <omp.h>

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

glm::ivec2 getChunkCoord(glm::ivec2 worldXZ);
glm::ivec2 getPosInChunk(glm::ivec2 worldXZ);

class ChunkManager;

typedef ChunkManager* ChunkManagerPtr;

float getAO(bool xmi,bool xpl,bool ymi,bool ypl,bool zmi,bool zpl);


#define PRISON
//#define TERRAIN
//#define CAVES

class Chunk {
private:
	std::vector<float>posData;
	std::vector<float>uvData;
	std::vector<float>aoMeshData;
	std::vector<unsigned int>triData;

	void addTriangle(unsigned int a,unsigned int b,unsigned int c);
	void addPos(float x,float y,float z);
	void addUV(float u,float v);
	void addUV(glm::vec2 v);
	void addUV(TexturePos tp,bool flip=false);
	void addAO(int x,int y,int z);
	void addTriangleFace(bool flip);

	Block getLocalBlock(int x,int y,int z);
	float getChunkAO(int x,int y,int z);

public:
	bool isEmpty(int x,int y,int z);

	Chunk();
	virtual ~Chunk();

	Chunk(int x,int z);

	ChunkManagerPtr cm;

	glm::ivec2 chunkPos;

	Chunk *cXMI;
	Chunk *cXPL;
	Chunk *cZMI;
	Chunk *cZPL;

	Block blockData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
	float 	 aoData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboUV;
	gl::VertexBuffer vboAO;
	gl::VertexBuffer ebo;

	bool instantiated=false;
	bool meshCreated=false;

	void createChunkData(FastNoise*fn);
	void prepareMesh(Atlas*atlas);
	void computeAO();
	void prepareGL();

	bool isEmptyReal(int x,int y,int z);

	glm::mat4 getModelMatrix();
	void render();
};

Chunk* emptyChunk();

#endif /* CHUNK_H_ */
