/*
 * Chunk.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: jack
 */

#include "Chunk.h"

Chunk::Chunk() {
	// TODO Auto-generated constructor stub
	for(int x=0;x<C_SIZE;x++){
		for(int y=0;y<C_HEIGHT;y++){
			for(int z=0;z<C_SIZE;z++){
				blockData[x][y][z]=blockEmpty;
			}
		}
	}
}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

void Chunk::createBuffers(){
	vao.create();
	vao.bind();

	vboPos=ChunkUtils::createStaticArrayFloatBuffer();
	vboPos.bind();
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);

	float posData[C_SIZE][C_HEIGHT][C_SIZE][3];
	for(int x=0;x<C_SIZE;x++){
		for(int y=0;y<C_HEIGHT;y++){
			for(int z=0;z<C_SIZE;z++){
				posData[x][y][z][0]=x;
				posData[x][y][z][1]=y;
				posData[x][y][z][2]=z;
			}
		}
	}
	vboPos.setData(sizeof(posData),posData);
	vboPos.unbind();

	gl::VertexBuffer vboXMI=ChunkUtils::createStaticArrayIntBuffer();
	vboXMI.bind();
	vboXMI.addVertexAttrib(1,1,false,1,(const GLvoid*)0);
	vboXMI.unbind();

	gl::VertexBuffer vboXPL=ChunkUtils::createStaticArrayIntBuffer();
	vboXPL.bind();
	vboXPL.addVertexAttrib(2,1,false,1,(const GLvoid*)0);
	vboXPL.unbind();

	gl::VertexBuffer vboYMI=ChunkUtils::createStaticArrayIntBuffer();
	vboYMI.bind();
	vboYMI.addVertexAttrib(3,1,false,1,(const GLvoid*)0);
	vboYMI.unbind();

	gl::VertexBuffer vboYPL=ChunkUtils::createStaticArrayIntBuffer();
	vboYPL.bind();
	vboYPL.addVertexAttrib(4,1,false,1,(const GLvoid*)0);
	vboYPL.unbind();

	gl::VertexBuffer vboZMI=ChunkUtils::createStaticArrayIntBuffer();
	vboZMI.bind();
	vboZMI.addVertexAttrib(5,1,false,1,(const GLvoid*)0);
	vboZMI.unbind();

	gl::VertexBuffer vboZPL=ChunkUtils::createStaticArrayIntBuffer();
	vboZPL.bind();
	vboZPL.addVertexAttrib(6,1,false,1,(const GLvoid*)0);
	vboZPL.unbind();

	vao.unbind();
}
void Chunk::updateBuffers(){
	for(int x=0;x<C_SIZE;x++){
		for(int y=0;y<C_HEIGHT;y++){
			for(int z=0;z<C_SIZE;z++){
				if(dirtyBlocks[x][y][z]){
					//Update block position (x,y,z)
					xmiData[x][y][z]=xplData[x][y][z]=ymiData[x][y][z]=yplData[x][y][z]=zmiData[x][y][z]=zplData[x][y][z]=false;
					if(!blockData[x][y][z].empty){
						printf("%i %i %i\n",x,y,z);
						if(x>0)if(blockData[x-1][y][z].empty)xmiData[x][y][z]=true;
						if(x<C_SIZE-1)if(blockData[x+1][y][z].empty)xplData[x][y][z]=true;
						if(y>0)if(blockData[x][y-1][z].empty)ymiData[x][y][z]=true;
						if(y<C_HEIGHT-1)if(blockData[x][y+1][z].empty)yplData[x][y][z]=true;
						if(z>0)if(blockData[x][y][z-1].empty)zmiData[x][y][z]=true;
						if(z<C_SIZE-1)if(blockData[x][y][z+1].empty)zplData[x][y][z]=true;
					}
					dirtyBlocks[x][y][z]=false;
				}
			}
		}
	}

	vao.bind();

	vboXMI.bind();
	vboXMI.setData(sizeof(xmiData),xmiData);
	vboXMI.unbind();

	vboXPL.bind();
	vboXPL.setData(sizeof(xplData),xplData);
	vboXPL.unbind();

	vboYMI.bind();
	vboYMI.setData(sizeof(ymiData),ymiData);
	vboYMI.unbind();

	vboYPL.bind();
	vboYPL.setData(sizeof(yplData),yplData);
	vboYPL.unbind();

	vboZMI.bind();
	vboZMI.setData(sizeof(zmiData),zmiData);
	vboZMI.unbind();

	vboZPL.bind();
	vboZPL.setData(sizeof(zplData),zplData);
	vboZPL.unbind();

	vao.unbind();
}

void Chunk::render(){
	vao.bind();
	glDrawArrays(GL_POINTS,0,C_SIZE*C_HEIGHT*C_SIZE);
	vao.unbind();
}

void Chunk::setBlock(int x,int y,int z,Block block){
	blockData[x][y][z]=block;
	dirtyBlocks[x][y][z]=true;
}
