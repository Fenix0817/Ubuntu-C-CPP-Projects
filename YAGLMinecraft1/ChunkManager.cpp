/*
 * ChunkManager.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: jack
 */

#include "ChunkManager.h"

ChunkManager::ChunkManager() {
	// TODO Auto-generated constructor stub

}

ChunkManager::~ChunkManager() {
	// TODO Auto-generated destructor stub
}

bool contains_ivec2(std::vector<glm::ivec2> list,glm::ivec2 v){
	for(unsigned int i=0;i<list.size();i++)if(list[i]==v)return true;
	return false;
}
bool contains_ivec3(std::vector<glm::ivec3> list,glm::ivec3 v){
	for(unsigned int i=0;i<list.size();i++)if(list[i]==v)return true;
	return false;
}

bool contains_lightnode(std::vector<LightNode*>list,LightNode*n){
	for(unsigned int i=0;i<list.size();i++)if(list[i]->pos==n->pos&&list[i]->val==n->val)return true;
	return false;
}

ChunkPtr ChunkManager::getChunk(int x,int z,bool instantiateChunk){
	bool foundChunk=false;
	ChunkPtr c=nullptr;
	for(unsigned int i=0;i<chunks.size()&&!foundChunk;i++){
		if(chunks[i]->chunkPos.x==x&&chunks[i]->chunkPos.y==z){
			c=chunks[i];
			foundChunk=true;
		}
	}
	if(!foundChunk){
#ifdef DEBUG_CHUNKMANAGER
		printf("\tCreating data for %i,%i\n",x,z);
#endif
		c=new Chunk();
		c->chunkPos=glm::ivec2(x,z);
		c->createChunkData(noise);
		chunks.push_back(c);
#ifdef DEBUG_CHUNKMANAGER
		printf("\tFinished creating data for %i,%i\n",x,z);
#endif
	}
	if(instantiateChunk){
		c->instantiated=true;
	}
	if(instantiateChunk&&!c->meshCreated){
#ifdef DEBUG_CHUNKMANAGER
		printf("\nInstantiating %i,%i\n",x,z);
#endif
		c->meshCreated=true;
		ChunkPtr xmi=getChunk(x-1,z,false);
		ChunkPtr xpl=getChunk(x+1,z,false);
		ChunkPtr zmi=getChunk(x,z-1,false);
		ChunkPtr zpl=getChunk(x,z+1,false);
		c->cXMI=xmi;
		c->cXPL=xpl;
		c->cZMI=zmi;
		c->cZPL=zpl;
//		setLighting(c);
		c->prepareMesh(atlas,false);
		c->prepareGL();
#ifdef DEBUG_CHUNKMANAGER
		printf("Finished instantiating %i,%i:  %i,%i,%i,%i\n",x,z,c->vao.id,c->vboPos.id,c->vboUV.id,c->ebo.id);
#endif
	}
	return c;
}

void ChunkManager::eraseChunk(int x,int z){
	for(unsigned int i=0;i<chunks.size();i++){
		if(chunks[i]->chunkPos==glm::ivec2(x,z)){
			chunks[i]->instantiated=false;
		}
	}
}

void ChunkManager::setBlock(int x,int y,int z,Block b){
	glm::ivec2 xz(x,z);
	glm::ivec2 chunkCoord=getChunkCoord(xz);
	glm::ivec2 pos=getPosInChunk(xz);
	ChunkPtr chunk=getChunk(chunkCoord.x,chunkCoord.y,false);
	chunk->blockData[pos.x][y][pos.y]=b;
}

void ChunkManager::addLight(int x,int y,int z,float f){
	Light*s=new Light();
	s->pos=glm::ivec3(x,y,z);
	s->val=f;
	s->initSpread(this);
	lights.push_back(s);
}

void ChunkManager::remeshChunk(int x,int z){
	ChunkPtr chunk=getChunk(x,z,false);
	ChunkPtr xmi=getChunk(x-1,z,false);
	ChunkPtr xpl=getChunk(x+1,z,false);
	ChunkPtr zmi=getChunk(x,z-1,false);
	ChunkPtr zpl=getChunk(x,z+1,false);
	chunk->cXMI=xmi;
	chunk->cXPL=xpl;
	chunk->cZMI=zmi;
	chunk->cZPL=zpl;
//	setLighting(chunk);
	chunk->prepareMesh(atlas,false);
	chunk->prepareGL();
}


void ChunkManager::render(gl::Shader shader,glm::mat4 vp){
	for(unsigned int i=0;i<chunks.size();i++){
		ChunkPtr c=chunks[i];
		if(c->instantiated){
			shader.setMat4("MVP",vp*c->getModelMatrix());
			c->render();
		}
	}
}

int ChunkManager::getNumChunksInMemory(){
	return chunks.size();
}

int ChunkManager::getNumChunksRendered(){
	int i=0;
	for(ChunkPtr c:chunks){
		if(c->instantiated)i++;
	}
	return i;
}

void ChunkManager::initLighting(){
	for(Light*l:lights){
		for(LightNode*n:l->closed){
			glm::ivec2 xz=glm::ivec2(n->pos.x,n->pos.z);
			glm::ivec2 c=getChunkCoord(xz);
			glm::ivec2 p=getPosInChunk(xz);
			getChunk(c.x,c.y,false)->lightData[p.x][n->pos.y][p.y]=0;
			addLightChange(n->pos);
//			updateLightMesh(n->pos,false);
		}
		l->initSpread(this);
	}
}

void ChunkManager::computeLighting(){
	for(Light*l:lights){
		if(!l->isDone()){
			l->stepSpread(this);
		}
	}
}

void ChunkManager::addLightChange(glm::ivec3 v){
	if(!contains_ivec3(lightChanges,v))lightChanges.push_back(v);
}

void ChunkManager::updateLightMesh(glm::ivec3 pos,bool sumLighting){
	glm::ivec2 v=getChunkCoord(glm::ivec2(pos.x,pos.z));
	glm::ivec2 p=getPosInChunk(glm::ivec2(pos.x,pos.z));
	ChunkPtr c=getChunk(v.x,v.y,false);
	if(c->instantiated){
//		printf("Re-setting light for chunk %i,%i\n",v.x,v.y);
		if(sumLighting)
			c->lightData[p.x][pos.y][p.y]=getLight(pos.x,pos.y,pos.z);
		c->prepareMesh(atlas,true);//Recreate mesh, only lighting
//		c->setLighting(this);
		c->prepareGL();
	}
}

float ChunkManager::getLight(int x,int y,int z){
	float f=0;
	for(Light*l:lights){
		f+=l->getValue(x,y,z);
	}
	return f;
}

void ChunkManager::storeFrameLightChanges(){
	if(lightChanges.size()>0){
		updateLightMesh(lightChanges[0],true);
		lightChanges.erase(lightChanges.begin());
	}
}

void ChunkManager::update(int frames,glm::ivec2 chunkPos){
	int chunkX=chunkPos.x;
	int chunkZ=chunkPos.y;

	for(int i=0;i<2;i++){
		computeLighting();
	}
	while(lightChanges.size()>0)storeFrameLightChanges();
	printf("Light changes.size() = %i\n",(int)lightChanges.size());

	int o=4;
	for(int x=-o;x<=o;x++){
		for(int z=-o;z<=o;z++){
			if(!contains_ivec2(chunksToAdd,glm::ivec2(x+chunkX,z+chunkZ))){
				chunksToAdd.push_back(glm::ivec2(x+chunkX,z+chunkZ));
			}
//				getChunk(x+chunkX,z+chunkZ,true);
		}
	}
	for(int i=0;i<10;i++){
		if(frames%1==0&&chunksToAdd.size()>0){
			glm::ivec2 chunkToAdd=chunksToAdd[0];
			getChunk(chunkToAdd.x,chunkToAdd.y,true);
			chunksToAdd.erase(chunksToAdd.begin());
		}
	}
	for(int i=0;i<200;i++){
		if(frames%1==0&&chunksToRemove.size()>0){
			glm::ivec2 chunkToRem=chunksToRemove[0];
			eraseChunk(chunkToRem.x,chunkToRem.y);
			chunksToRemove.erase(chunksToRemove.begin());
		}
	}

	for(unsigned int i=0;i<chunks.size();i++){
		float d=max(abs(chunks[i]->chunkPos.x-chunkX),abs(chunks[i]->chunkPos.y-chunkZ));
		if(d>o+2&&!contains_ivec2(chunksToRemove,chunks[i]->chunkPos))chunksToRemove.push_back(chunks[i]->chunkPos);
	}
}

Block ChunkManager::getBlock(int x,int y,int z){
	glm::ivec2 chunkPos=getChunkCoord(glm::ivec2(x,z));
	glm::ivec2 posInChunk=getPosInChunk(glm::ivec2(x,z));
	ChunkPtr c=getChunk(chunkPos.x,chunkPos.y,false);
	return c->blockData[posInChunk.x][y][posInChunk.y];
}
Block ChunkManager::getBlock(glm::ivec3 p){
	return getBlock(p.x,p.y,p.z);
}

//In world coordinates, not pos in chunk coordinates
Intersection ChunkManager::intersectWorld(glm::vec3 start,glm::vec3 dir,float range){
	//Line 70 of https://bitbucket.org/volumesoffun/polyvox/src/9a71004b1e72d6cf92c41da8995e21b652e6b836/include/PolyVox/Raycast.inl?at=develop&fileviewer=file-view-default
	//Don't use the callbacks until later

	glm::vec3 end=start+dir*range;

	float o=0;
	const float x1=start.x+o;
	const float y1=start.y+o;
	const float z1=start.z+o;
	const float x2=end.x+o;
	const float y2=end.y+o;
	const float z2=end.z+o;

	int i=floor(x1);
	int j=floor(y1);
	int k=floor(z1);

//	const int iend=floor(x2);
//	const int jend=floor(y2);
//	const int kend=floor(z2);

	const int di = ((x1 < x2) ? 1 : ((x1 > x2) ? -1 : 0));
	const int dj = ((y1 < y2) ? 1 : ((y1 > y2) ? -1 : 0));
	const int dk = ((z1 < z2) ? 1 : ((z1 > z2) ? -1 : 0));

	const float deltax=1/std::abs(x2-x1);
	const float deltay=1/std::abs(y2-y1);
	const float deltaz=1/std::abs(z2-z1);

	const float minx=floor(x1),maxx=minx+1;
	float tx=((x1>x2)?(x1-minx):(maxx-x1))*deltax;

	const float miny=floor(y1),maxy=miny+1;
	float ty=((y1>y2)?(y1-miny):(maxy-y1))*deltay;

	const float minz=floor(z1),maxz=minz+1;
	float tz=((z1>z2)?(z1-minz):(maxz-z1))*deltaz;

	std::vector<glm::ivec3>list;

	for(int num=0;num<range;num++){
		if(j<0||j>=CHUNK_HEIGHT)break;
		list.push_back(glm::ivec3(i,j,k));
		if(tx<=ty&&tx<=tz){
			//if(i==iend)break;
			tx+=deltax;
			i+=di;

			//if(di==1)sampler.movePositiveX();
			//if(di==-1)sampler.moveNegativeX();
		}else if(ty<=tz){
			//if(j==jend)break;
			ty+=deltay;
			j+=dj;

			//if(dj==1)sampler.movePositiveY();
			//if(dj==-1)sampler.moveNegativeY();
		}else{
			//if(k==kend)break;
			tz+=deltaz;
			k+=dk;

			//if(dk==1)sampler.movePositiveZ();
			//if(dk==-1)sampler.moveNegativeZ();
		}
	}

	for(unsigned int i=1;i<list.size();i++){//Start at 1, so that when retrieving previous block list[i-1] we stay inside the array
		if(!getBlock(list[i]).empty){
//			printf("Intersection at %i,%i,%i   ",list[i].x,list[i].y,list[i].z);
			return Intersection(list[i],list[i-1]);
		}
	}
//	Block camBlock=getBlock(start);
//	if(!camBlock.empty)printf("CAMERA INSIDE TERRAIN\n");

//	start+=dir;
//
//	float x=floor(start.x);
//	float y=floor(start.y);
//	float z=floor(start.z);
//
//	float dx=dir.x;
//	float dy=dir.y;
//	float dz=dir.z;
//
//	float stepX=sign(dx);
//	float stepY=sign(dy);
//	float stepZ=sign(dz);
//
//	float tMaxX=intbound(start.x,dx);
//	float tMaxY=intbound(start.y,dy);
//	float tMaxZ=intbound(start.z,dz);
//
//	float tDeltaX=stepX/dx;
//	float tDeltaY=stepY/dy;
//	float tDeltaZ=stepZ/dz;
//
//	std::vector<glm::ivec3>blocks;
//
//	for(int i=0;i<range;i++){
//		if(tMaxX<tMaxY){
//			if(tMaxX<tMaxZ){
//				x+=stepX;
//				tMaxX+=tDeltaX;
//				//normal of this face is -1,0,0
//			}else{
//				z+=stepZ;
//				tMaxZ+=tDeltaZ;
//				//normal of this face is 0,0,-1
//			}
//		}else{
//			if(tMaxY<tMaxZ){
//				y+=stepY;
//				tMaxY+=tDeltaY;
//				//normal of this face is 0,-1,0
//			}else{
//				z+=stepZ;
//				tMaxZ+=tDeltaZ;
//				//normal of this face is 0,0,-1
//			}
//		}
//		blocks.push_back(glm::ivec3(x,y,z));
//	}
//
//	for(glm::ivec3 p:blocks){
//		if(!getBlock(p).empty)return Intersection(p);
//	}

	return Intersection(false);
}
