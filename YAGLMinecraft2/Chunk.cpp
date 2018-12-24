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

glm::mat4 Chunk::getModelMatrix(){
	return glm::translate(glm::mat4(1),glm::vec3(pos.x*C_SIZE,0,pos.y*C_SIZE));
}

void Chunk::createBuffers(){
	vao.create();
	vao.bind();

	vboPos=ChunkUtils::createStaticArrayFloatBuffer();
	vboPos.bind();
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);

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

	xmi.init(1);
	xpl.init(2);
	ymi.init(3);
	ypl.init(4);
	zmi.init(5);
	zpl.init(6);

	vao.unbind();
}
void Chunk::updateBuffers(Atlas*atlas,Chunk*cxmi,Chunk*cxpl,Chunk*czmi,Chunk*czpl){
	for(int x=0;x<C_SIZE;x++){
		for(int y=0;y<C_HEIGHT;y++){
			for(int z=0;z<C_SIZE;z++){
//				if(dirtyBlocks[x][y][z]){
					//Update block position (x,y,z)
					xmi.visData[x][y][z]=xpl.visData[x][y][z]=ymi.visData[x][y][z]=ypl.visData[x][y][z]=zmi.visData[x][y][z]=zpl.visData[x][y][z]=true;
//					if(x==0)xmi.visData[x][y][z]=true;
//					if(z==0)zmi.visData[x][y][z]=true;
//					if(x==C_SIZE-1)xpl.visData[x][y][z]=true;
//					if(z==C_SIZE-1)zpl.visData[x][y][z]=true;
					if(blockData[x][y][z].empty){
//						printf("%i %i %i\n",x,y,z);
//						if(x>0)if(blockData[x-1][y][z].empty)xmi.visData[x][y][z]=true;
//						if(x<C_SIZE-1)if(blockData[x+1][y][z].empty)xpl.visData[x][y][z]=true;
//						if(y>0)if(blockData[x][y-1][z].empty)ymi.visData[x][y][z]=true;
//						if(y<C_HEIGHT-1)if(blockData[x][y+1][z].empty)ypl.visData[x][y][z]=true;
//						if(z>0)if(blockData[x][y][z-1].empty)zmi.visData[x][y][z]=true;
//						if(z<C_SIZE-1)if(blockData[x][y][z+1].empty)zpl.visData[x][y][z]=true;
						xmi.visData[x][y][z]=xpl.visData[x][y][z]=ymi.visData[x][y][z]=ypl.visData[x][y][z]=zmi.visData[x][y][z]=zpl.visData[x][y][z]=false;
					}else{
						if(x>0)if(!blockData[x-1][y][z].empty)xmi.visData[x][y][z]=false;
						if(x<C_SIZE-1)if(!blockData[x+1][y][z].empty)xpl.visData[x][y][z]=false;
						if(y>0)if(!blockData[x][y+1][z].empty)ymi.visData[x][y][z]=false;
						if(y<C_HEIGHT-1)if(!blockData[x][y-1][z].empty)ypl.visData[x][y][z]=false;
						if(z>0)if(!blockData[x][y][z-1].empty)zmi.visData[x][y][z]=false;
						if(z<C_SIZE-1)if(!blockData[x][y][z+1].empty)zpl.visData[x][y][z]=false;
					}
					xmi.setUV(x,y,z,atlas->getAtlasPos(blockData[x][y][z].xmi));
					xpl.setUV(x,y,z,atlas->getAtlasPos(blockData[x][y][z].xpl));
					ymi.setUV(x,y,z,atlas->getAtlasPos(blockData[x][y][z].ymi));
					ypl.setUV(x,y,z,atlas->getAtlasPos(blockData[x][y][z].ypl));
					zmi.setUV(x,y,z,atlas->getAtlasPos(blockData[x][y][z].zmi));
					zpl.setUV(x,y,z,atlas->getAtlasPos(blockData[x][y][z].zpl));
//					xmiData[x][y][z]=xplData[x][y][z]=ymiData[x][y][z]=yplData[x][y][z]=zmiData[x][y][z]=zplData[x][y][z]=true;
//					if(!blockData[x][y][z].empty)
//					dirtyBlocks[x][y][z]=false;
//				}
			}
		}
	}

	vao.bind();

	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.unbind();

	xmi.updateBuffers();
	xpl.updateBuffers();
	ymi.updateBuffers();
	ypl.updateBuffers();
	zmi.updateBuffers();
	zpl.updateBuffers();

	vao.unbind();
}

void Chunk::render(){
	vao.bind();
	glDrawArrays(GL_POINTS,0,C_SIZE*C_HEIGHT*C_SIZE);
	vao.unbind();
}

void Chunk::setBlock(int x,int y,int z,Block block){
	blockData[x][y][z]=block;
	dirtyBlocks[x][C_HEIGHT-y-1][z]=true;
}
