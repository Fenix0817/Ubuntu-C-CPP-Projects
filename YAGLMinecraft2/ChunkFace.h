/*
 * ChunkFace.h
 *
 *  Created on: Nov 19, 2018
 *      Author: jack
 */

#ifndef CHUNKFACE_H_
#define CHUNKFACE_H_

#include "ChunkUtils.h"
#include "config.h"

class ChunkFace {
public:
	ChunkFace();
	virtual ~ChunkFace();

	gl::VertexBuffer vboVis;
	gl::VertexBuffer vboUV;

	int visData[C_SIZE][C_HEIGHT][C_SIZE];
	float uvData[C_SIZE][C_HEIGHT][C_SIZE][2];

	void init(int num);

	void setVis(int x,int y,int z,bool b);
	void setUV(int x,int y,int z,float u,float v);

	void updateVisBuffer();
	void updateUVBuffer();
	void updateBuffers();
};

#endif /* CHUNKFACE_H_ */
