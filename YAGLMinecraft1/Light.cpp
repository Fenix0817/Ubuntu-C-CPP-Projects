/*
 * Light.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: jack
 */

#include "Light.h"
#include "ChunkManager.h"

Light::Light() {
	// TODO Auto-generated constructor stub

}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::initSpread(ChunkManager*cm){
	open.clear();
	closed.clear();

	if(cm->getBlock(pos.x,pos.y,pos.z).empty){
		LightNode*lightNode=new LightNode();
		lightNode->pos=pos;
		lightNode->val=val;
		open.push_back(lightNode);
	}
}
void Light::stepSpread(ChunkManager*cm){
	changes.clear();
	int index=0;
	for(unsigned int i=0;i<open.size();i++){
		int x=open[i]->pos.x;
		int y=open[i]->pos.y;
		int z=open[i]->pos.z;
		if( ( (!cm->getBlock(x-1,y,z).empty)  &&  (!cm->getBlock(x+1,y,z).empty) && (!cm->getBlock(x,y-1,z).empty) && (!cm->getBlock(x,y+1,z).empty) && (!cm->getBlock(x,y,z-1).empty) && (!cm->getBlock(x,y,z+1).empty))){
			index=i;
			break;
		}
	}
	LightNode*node=open[index];
	open.erase(open.begin()+index);
	if(!contains_lightnode(open,node)&&!contains_lightnode(closed,node)){
		closed.push_back(node);
		if(node->val>df){
			int ix=(int)node->pos.x;
			int iy=(int)node->pos.y;
			int iz=(int)node->pos.z;
			changes.push_back(glm::ivec3(ix,iy,iz));
			float f=node->val;
			if(cm->getBlock(glm::ivec3(ix-1,iy,iz)).empty)open.push_back(new_lightnode(ix-1,iy,iz,f-df));
			if(cm->getBlock(glm::ivec3(ix+1,iy,iz)).empty)open.push_back(new_lightnode(ix+1,iy,iz,f-df));
			if(cm->getBlock(glm::ivec3(ix,iy-1,iz)).empty)open.push_back(new_lightnode(ix,iy-1,iz,f-df));
			if(cm->getBlock(glm::ivec3(ix,iy+1,iz)).empty)open.push_back(new_lightnode(ix,iy+1,iz,f-df));
			if(cm->getBlock(glm::ivec3(ix,iy,iz-1)).empty)open.push_back(new_lightnode(ix,iy,iz-1,f-df));
			if(cm->getBlock(glm::ivec3(ix,iy,iz+1)).empty)open.push_back(new_lightnode(ix,iy,iz+1,f-df));
		}
	}

	for(glm::ivec3 v:changes){
		cm->addLightChange(v);
	}
}
float Light::getValue(int x,int y,int z){
	for(LightNode*node:closed){
		if(node->pos==glm::ivec3(x,y,z)){
			return node->val;
		}
	}
	return 0;
}
bool Light::isDone(){
	//open.size()>0 => false
	//open.size()==0 => true
	return open.size()==0;
}
//
//void Light::propogate(ChunkManager*cm){
//	nodes.clear();
//	float df=0.1;
//	std::vector<LightNode*>open;
//	std::vector<LightNode*>closed;
//
//	LightNode*lightNode=new LightNode();
//	lightNode->pos=pos;
//	lightNode->val=val;
//	open.push_back(lightNode);
//	while(open.size()>0){
//	}
//
//	for(LightNode*n:closed){
//		nodes.push_back(n);
//		cm->addLightChange(getChunkCoord(glm::ivec2(n->pos.x,n->pos.z)));
//	}
//}

void Light::storeLight(ChunkManager*cm){
//	for(LightNode*l:nodes){
//		glm::ivec2 c=getChunkCoord(glm::ivec2(l->pos.x,l->pos.z));
//		glm::ivec2 p=getPosInChunk(glm::ivec2(l->pos.x,l->pos.z));
//		cm->getChunk(c.x,c.y,false)->lightData[p.x][l->pos.y][p.y]=l->val;
//	}
}

bool Light::needsUpdateOnAdd(int x,int y,int z){//Does this light need to be updated on block addition at (x,y,z)
	return true;
}
bool Light::needsUpdateOnRem(int x,int y,int z){//Does this light need to be updated on block removal at (x,y,z)
	return true;
}
