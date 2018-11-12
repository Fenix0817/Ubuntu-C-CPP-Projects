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

#include "Atlas.h"
#include "AtlasPos.h"
#include "Block.h"
#include "BlockFace.h"

#define C_SIZE 16
#define C_HEIGHT 32

namespace ChunkUtils {

inline gl::VertexBuffer createStaticArrayFloatBuffer(){
	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Float);
	vbo.create();
	return vbo;
}

inline gl::VertexBuffer createStaticArrayIntBuffer(){
	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Int);
	vbo.create();
	return vbo;
}

}

class Chunk {
public:
	Chunk();
	virtual ~Chunk();

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboXMI,vboXPL,vboYMI,vboYPL,vboZMI,vboZPL;

	int xmiData[C_SIZE][C_HEIGHT][C_SIZE];
	int xplData[C_SIZE][C_HEIGHT][C_SIZE];
	int ymiData[C_SIZE][C_HEIGHT][C_SIZE];
	int yplData[C_SIZE][C_HEIGHT][C_SIZE];
	int zmiData[C_SIZE][C_HEIGHT][C_SIZE];
	int zplData[C_SIZE][C_HEIGHT][C_SIZE];

	Block blockData[C_SIZE][C_HEIGHT][C_SIZE];

	void createBuffers();
	void updateBuffers();

	void render();

	void setBlock(int x,int y,int z,Block block);

private:
	bool dirtyBlocks[C_SIZE][C_HEIGHT][C_SIZE];
};

#endif /* CHUNK_H_ */
