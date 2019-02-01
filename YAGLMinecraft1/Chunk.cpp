/*
 * Chunk.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#include "Chunk.h"
#include "ChunkManager.h"
glm::vec4 fmod(glm::vec4 v,float f){return glm::vec4(fmod(v.x,f),fmod(v.y,f),fmod(v.z,f),fmod(v.w,f));}
glm::vec3 fmod(glm::vec3 v,float f){return glm::vec3(fmod(v.x,f),fmod(v.y,f),fmod(v.z,f));}
glm::vec4 permute(glm::vec4 x){return fmod(((x*34.0f)+1.0f)*x, 289.0f);}
glm::vec4 taylorInvSqrt(glm::vec4 r){return 1.79284291400159f - 0.85373472095314f * r;}
glm::vec3 fade(glm::vec3 t) {return t*t*t*(t*(t*6.0f-15.0f)+10.0f);}

float cnoise(glm::vec3 P){
	using namespace glm;
  vec3 Pi0 = floor(P); // Integer part for indexing
  vec3 Pi1 = Pi0 + vec3(1.0); // Integer part + 1
  Pi0 = fmod(Pi0, 289.0);
  Pi1 = fmod(Pi1, 289.0);
  vec3 Pf0 = fract(P); // Fractional part for interpolation
  vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
  vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
  vec4 iy = vec4(Pi0.y,Pi0.y, Pi1.y,Pi1.y);
  vec4 iz0 = glm::vec4(Pi0.z);
  vec4 iz1 = glm::vec4(Pi1.z);

  vec4 ixy = permute(permute(ix) + iy);
  vec4 ixy0 = permute(ixy + iz0);
  vec4 ixy1 = permute(ixy + iz1);

  vec4 gx0 = ixy0 / 7.0f;
  vec4 gy0 = fract(floor(gx0) / 7.0f) - 0.5f;
  gx0 = fract(gx0);
  vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
  vec4 sz0 = step(gz0, vec4(0.0));
  gx0 -= sz0 * (step(0.0f, gx0) - 0.5f);
  gy0 -= sz0 * (step(0.0f, gy0) - 0.5f);

  vec4 gx1 = ixy1 / 7.0f;
  vec4 gy1 = fract(floor(gx1) / 7.0f) - 0.5f;
  gx1 = fract(gx1);
  vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
  vec4 sz1 = step(gz1, vec4(0.0));
  gx1 -= sz1 * (step(0.0f, gx1) - 0.5f);
  gy1 -= sz1 * (step(0.0f, gy1) - 0.5f);

  vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
  vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
  vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
  vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
  vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
  vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
  vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
  vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

  vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
  g000 *= norm0.x;
  g010 *= norm0.y;
  g100 *= norm0.z;
  g110 *= norm0.w;
  vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
  g001 *= norm1.x;
  g011 *= norm1.y;
  g101 *= norm1.z;
  g111 *= norm1.w;

  float n000 = glm::dot(g000, Pf0);
  float n100 = glm::dot(g100, vec3(Pf1.x, Pf0.y,Pf0.z));
  float n010 = glm::dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
  float n110 = glm::dot(g110, vec3(Pf1.x,Pf1.y, Pf0.z));
  float n001 = glm::dot(g001, vec3(Pf0.x,Pf0.y, Pf1.z));
  float n101 = glm::dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
  float n011 = glm::dot(g011, vec3(Pf0.x, Pf1.y,Pf1.z));
  float n111 = glm::dot(g111, Pf1);

  vec3 fade_xyz = fade(Pf0);
  vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
  vec2 n_yz = mix(glm::vec2(n_z.x,n_z.y), glm::vec2(n_z.z,n_z.w), fade_xyz.y);
  float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x);
  return 2.2 * n_xyz;
}

float getAO(float xmi,float xpl,float ymi,float ypl,float zmi,float zpl){
	return ypl;
//	return (xmi+xpl+ymi+ypl+zmi+zpl)/6.0f;
//	return ( (xmi||xpl)+(ymi||ypl)+(zmi||zpl)  )/3.0f;
//	return (xmi+xpl+zmi+zpl)/4.0f;
//	return (xpl+zpl)/2.0f;
//	return xmi;
	//Fix block offseting problem
//	bool bs1=xmi||xpl;
//	bool bs2=zmi||zpl;
//	bool bc=ymi||ypl;
//	int s1=bs1;
//	int s2=bs2;
//	int c=bc;
//	if(bs1&&bs2)return 0;
//	return 3-s1-s2-c;
//	return cnoise(glm::vec3(x*0.5,y*0.5,z*0.5));
//	return ((float)rand())/((float)RAND_MAX);
//	return 1;
//	return (xmi+xpl+ymi+ypl+zmi+zpl)/6.0f;
//	return
}

//Get chunk position
glm::ivec2 getChunkCoord(glm::ivec2 worldXZ){
	glm::ivec2 offset=getPosInChunk(worldXZ);
	worldXZ-=offset;
	return worldXZ/CHUNK_SIZE;
}
//Get position in chunk
glm::ivec2 getPosInChunk(glm::ivec2 worldXZ){
	while(worldXZ.x<0)worldXZ.x+=CHUNK_SIZE;
	while(worldXZ.y<0)worldXZ.y+=CHUNK_SIZE;
	while(worldXZ.x>=CHUNK_SIZE)worldXZ.x-=CHUNK_SIZE;
	while(worldXZ.y>=CHUNK_SIZE)worldXZ.y-=CHUNK_SIZE;
	return worldXZ;
}

Chunk::Chunk() {
	// TODO Auto-generated constructor stub
//	for(int x=0;x<CHUNK_SIZE;x++){
//		for(int y=0;y<CHUNK_HEIGHT;y++){
//			for(int z=0;z<CHUNK_SIZE;z++){
//				lightData[x][y][z]=((float)rand())/((float)RAND_MAX);
//			}
//		}
//	}
}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}


Chunk::Chunk(int x,int z){
	chunkPos=glm::ivec2(x,z);
//	for(int x=0;x<CHUNK_SIZE;x++){
//		for(int y=0;y<CHUNK_HEIGHT;y++){
//			for(int z=0;z<CHUNK_SIZE;z++){
//				torchlightData[x][y][z]=0.3;
//			}
//		}
//	}
}

Chunk* emptyChunk(){
	Chunk* c=new Chunk();
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int y=0;y<CHUNK_HEIGHT;y++){
			for(int z=0;z<CHUNK_SIZE;z++){
				c->blockData[x][y][z]=blockEmpty;
			}
		}
	}
	return c;
}

void Chunk::clearLight(){
#pragma omp parallel for
	for(int x=0;x<CHUNK_SIZE;x++){
#pragma omp parallel for
		for(int y=0;y<CHUNK_HEIGHT;y++){
#pragma omp parallel for
			for(int z=0;z<CHUNK_SIZE;z++){
				torchlightData[x][y][z]=0;
			}
		}
	}
}

void Chunk::addTriangle(unsigned int a,unsigned int b,unsigned int c){
	unsigned int i=posData.size()/3;
	triData.push_back(i+a);
	triData.push_back(i+b);
	triData.push_back(i+c);
}
void Chunk::addPos(float x,float y,float z){
	posData.push_back(x);
	posData.push_back(y);
	posData.push_back(z);
}
void Chunk::addUV(float u,float v){
	uvData.push_back(u);
	uvData.push_back(v);
}
void Chunk::addUV(glm::vec2 v){
	addUV(v.x,v.y);
}
void Chunk::addUV(TexturePos tp,bool flip){
	addUV(tp._00);
	if(flip){
		addUV(tp._10);
		addUV(tp._01);
	}else{
		addUV(tp._01);
		addUV(tp._10);
	}
	addUV(tp._11);
}
float Chunk::getChunkAO(int x,int y,int z){
	//-1,0,-1
	//-1,0,0
	//0,0,-1
	//0,0,0
	return (isEmpty(x-1,y,z-1)+isEmpty(x-1,y,z)+isEmpty(x,y,z-1)+isEmpty(x,y,z)+
			isEmpty(x-1,y-1,z-1)+isEmpty(x-1,y-1,z)+isEmpty(x,y-1,z-1)+isEmpty(x,y-1,z))/8.0f;
}
void Chunk::addAO(int x,int y,int z){
	aoMeshData.push_back(getChunkAO(x,y,z));
}
void Chunk::addTriangleFace(bool flip){
	if(flip){
		addTriangle(0,1,3);
		addTriangle(0,2,3);
	}else{
		addTriangle(0,1,2);
		addTriangle(1,2,3);
	}
}

bool Chunk::isEmpty(int x,int y,int z){
	if(
//			x<0||x>=CHUNK_SIZE||
			y<0||y>=CHUNK_HEIGHT
//			||z<0||z>=CHUNK_SIZE
			)return true;
	if(x<0)return cXMI->isEmptyReal(x+CHUNK_SIZE,y,z);
	if(x>=CHUNK_SIZE)return cXPL->isEmptyReal(x-CHUNK_SIZE,y,z);
	if(z<0)return cZMI->isEmptyReal(x,y,z+CHUNK_SIZE);
	if(z>=CHUNK_SIZE)return cZPL->isEmptyReal(x,y,z-CHUNK_SIZE);
//	if(y<0||y>=CHUNK_HEIGHT)return true;
	return isEmptyReal(x,y,z);
}

float Chunk::getTorchlight(int x,int y,int z){
	if(y<0||y>=CHUNK_HEIGHT)return true;
	if(x<0)return cXMI->torchlightData[x+CHUNK_SIZE][y][z];
	if(x>=CHUNK_SIZE)return cXPL->torchlightData[x-CHUNK_SIZE][y][z];
	if(z<0)return cZMI->torchlightData[x][y][z+CHUNK_SIZE];
	if(z>=CHUNK_SIZE)return cZPL->torchlightData[x][y][z-CHUNK_SIZE];
	return torchlightData[x][y][z];
}

Block Chunk::getLocalBlock(int x,int y,int z){
//	printf("%i,%i,%i\n",x,y,z);
	if(x<0){
		if(cXMI!=nullptr)return cXMI->blockData[x+CHUNK_SIZE][y][z];
		else return blockEmpty;
	}
	if(z<0){
		if(cZMI!=nullptr)return cZMI->blockData[x][y][z+CHUNK_SIZE];
		else return blockEmpty;
	}
	if(x>=CHUNK_SIZE){
		if(cXPL!=nullptr)return cXPL->blockData[x-CHUNK_SIZE][y][z];
		else return blockEmpty;
	}
	if(z>=CHUNK_SIZE){
		if(cZPL!=nullptr)return cZPL->blockData[x][y][z-CHUNK_SIZE];
		else return blockEmpty;
	}
	if(y<0||y>=CHUNK_HEIGHT)return blockEmpty;
	return blockData[x][y][z];
}

bool Chunk::isEmptyReal(int x,int y,int z){
	return blockData[x][y][z].empty;
}

void Chunk::createChunkData(FastNoisePtr fn,WorldGenerator*wg){
	wg->generateData(chunkPos.x*CHUNK_SIZE,chunkPos.y*CHUNK_SIZE,blockData);
}

void Chunk::computeAO(){
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int y=0;y<CHUNK_HEIGHT;y++){
			for(int z=0;z<CHUNK_SIZE;z++){
				aoData[x][y][z]=getChunkAO(x,y,z);
			}
		}
	}
}

void Chunk::addTorchlight(int x,int y,int z){
	float f=(rand()%1000)/1000.0;
	for(int i=0;i<4;i++){
		torchlightMeshData.push_back(torchlightData[x][y][z]);
	}
}

void Chunk::prepareMesh(Atlas*atlas){
	posData.clear();
	uvData.clear();
	triData.clear();
	aoMeshData.clear();
	torchlightMeshData.clear();
	computeAO();
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int y=0;y<CHUNK_HEIGHT;y++){
			for(int z=0;z<CHUNK_SIZE;z++){

				Block b=blockData[x][y][z];

				if(b.empty)continue;

				TexturePos xmiTP=atlas->getTexturePos(b.xmi);
				TexturePos xplTP=atlas->getTexturePos(b.xpl);
				TexturePos ymiTP=atlas->getTexturePos(b.ymi);
				TexturePos yplTP=atlas->getTexturePos(b.ypl);
				TexturePos zmiTP=atlas->getTexturePos(b.zmi);
				TexturePos zplTP=atlas->getTexturePos(b.zpl);

				if(isEmpty(x-1,y,z)){//xmi
					float a00=getChunkAO(x,y,z);
					float a01=getChunkAO(x,y,z+1);
					float a11=getChunkAO(x,y+1,z+1);
					float a10=getChunkAO(x,y+1,z);
					addTriangleFace(a00+a11>a01+a10);
					addPos(x,y,z);
					addPos(x,y+1,z);
					addPos(x,y,z+1);
					addPos(x,y+1,z+1);
					addUV(xmiTP);
					addAO(x,y,z);
					addAO(x,y+1,z);
					addAO(x,y,z+1);
					addAO(x,y+1,z+1);
					addTorchlight(x-1,y,z);
				}

				if(isEmpty(x+1,y,z)){//xpl
					float a00=getChunkAO(x+1,y,z);
					float a01=getChunkAO(x+1,y,z+1);
					float a11=getChunkAO(x+1,y+1,z+1);
					float a10=getChunkAO(x+1,y+1,z);
					addTriangleFace(a00+a11>a01+a10);
					addPos(x+1,y,z);
					addPos(x+1,y+1,z);
					addPos(x+1,y,z+1);
					addPos(x+1,y+1,z+1);
					addAO(x+1,y,z);
					addAO(x+1,y+1,z);
					addAO(x+1,y,z+1);
					addAO(x+1,y+1,z+1);
					addUV(xplTP);
					addTorchlight(x+1,y,z);
				}

				if(isEmpty(x,y-1,z)){//ymi
					float a00=getChunkAO(x,y,z);
					float a01=getChunkAO(x,y,z+1);
					float a11=getChunkAO(x+1,y,z+1);
					float a10=getChunkAO(x+1,y,z);
					addTriangleFace(a00+a11>a01+a10);
					addPos(x,y,z);
					addPos(x+1,y,z);
					addPos(x,y,z+1);
					addPos(x+1,y,z+1);
					addAO(x,y,z);
					addAO(x+1,y,z);
					addAO(x,y,z+1);
					addAO(x+1,y,z+1);
					addUV(ymiTP);
					addTorchlight(x,y-1,z);
				}

				if(isEmpty(x,y+1,z)){//ypl
					float a00=getChunkAO(x,y+1,z);
					float a01=getChunkAO(x,y+1,z+1);
					float a11=getChunkAO(x+1,y+1,z+1);
					float a10=getChunkAO(x+1,y+1,z);
					addTriangleFace(a00+a11>a01+a10);
					addPos(x,y+1,z);
					addPos(x+1,y+1,z);
					addPos(x,y+1,z+1);
					addPos(x+1,y+1,z+1);
					addAO(x,y+1,z);
					addAO(x+1,y+1,z);
					addAO(x,y+1,z+1);
					addAO(x+1,y+1,z+1);
					addUV(yplTP);
					addTorchlight(x,y+1,z);
				}

				if(isEmpty(x,y,z-1)){//zmi
					float a00=getChunkAO(x,y,z);
					float a01=getChunkAO(x,y+1,z);
					float a11=getChunkAO(x+1,y+1,z);
					float a10=getChunkAO(x+1,y,z);
					addTriangleFace(a00+a11>a01+a10);
					addPos(x,y,z);
					addPos(x,y+1,z);
					addPos(x+1,y,z);
					addPos(x+1,y+1,z);
					addAO(x,y,z);
					addAO(x,y+1,z);
					addAO(x+1,y,z);
					addAO(x+1,y+1,z);
					addUV(zmiTP);
					addTorchlight(x,y,z-1);
				}

				if(isEmpty(x,y,z+1)){//zpl
					float a00=getChunkAO(x,y,z+1);
					float a01=getChunkAO(x,y+1,z+1);
					float a11=getChunkAO(x+1,y+1,z+1);
					float a10=getChunkAO(x+1,y,z+1);
					addTriangleFace(a00+a11>a01+a10);
					addPos(x,y,z+1);
					addPos(x,y+1,z+1);
					addPos(x+1,y,z+1);
					addPos(x+1,y+1,z+1);
					addAO(x,y,z+1);
					addAO(x,y+1,z+1);
					addAO(x+1,y,z+1);
					addAO(x+1,y+1,z+1);
					addUV(zplTP);
					addTorchlight(x,y,z+1);
				}

			}
		}
	}
}

void Chunk::prepareGL(){
	if(vao.isCreated()){
		vao.bind();

		vboPos.bind();
		vboPos.setData(sizeof(float)*posData.size(),posData.data());
		vboPos.unbind();

		vboUV.bind();
		vboUV.setData(sizeof(float)*uvData.size(),uvData.data());
		vboUV.unbind();

		vboAO.bind();
		vboAO.setData(sizeof(float)*aoMeshData.size(),aoMeshData.data());
		vboAO.unbind();

		vboTorchlight.bind();
		vboTorchlight.setData(sizeof(float)*torchlightMeshData.size(),torchlightMeshData.data());
		vboTorchlight.unbind();

		ebo.bind();
		ebo.setData(sizeof(unsigned int)*triData.size(),triData.data());
		ebo.unbind();

		vao.unbind();
		return;
	}

	vao.create();
	vao.bind();

	vboPos=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(float)*posData.size(),posData.data());
	vboPos.addVertexAttrib(0,3,false,3,0);
	vboPos.unbind();

	vboUV=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(float)*uvData.size(),uvData.data());
	vboUV.addVertexAttrib(1,2,false,2,0);
	vboUV.unbind();

	vboAO=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboAO.create();
	vboAO.bind();
	vboAO.setData(sizeof(float)*aoMeshData.size(),aoMeshData.data());
	vboAO.addVertexAttrib(3,1,false,1,0);
	vboAO.unbind();

	vboTorchlight=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboTorchlight.create();
	vboTorchlight.bind();
	vboTorchlight.setData(sizeof(float)*torchlightMeshData.size(),torchlightMeshData.data());
	vboTorchlight.addVertexAttrib(4,1,false,1,0);

	ebo=gl::VertexBuffer(gl::VertexBufferTarget::ElementArray,gl::VertexBufferUsage::StaticDraw,gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(unsigned int)*triData.size(),triData.data());
	ebo.unbind();

	vao.unbind();

}
void Chunk::setTorchlight(int x,int y,int z,float l){
//	if(y<0||y>=CHUNK_HEIGHT)return;
//	if(x<0&&cXMI!=nullptr)cXMI->setTorchlight(x+CHUNK_SIZE,y,z,l);
//	if(z<0&&cZMI!=nullptr)cZMI->setTorchlight(x,y,z+CHUNK_SIZE,l);
//	if(x>=CHUNK_SIZE&&cXPL!=nullptr)cXPL->setTorchlight(x-CHUNK_SIZE,y,z,l);
//	if(x>=CHUNK_SIZE&&cZPL!=nullptr)cZPL->setTorchlight(x,y,z-CHUNK_SIZE,l);
	if(x<0||y<0||z<0||x>=CHUNK_SIZE||y>=CHUNK_HEIGHT||z>=CHUNK_SIZE)printf("%i,%i,%i\n",x,y,z);
	else torchlightData[x][y][z]=l;
}

glm::mat4 Chunk::getModelMatrix(){
	return glm::translate(glm::mat4(1),glm::vec3(CHUNK_SIZE*chunkPos.x,0,CHUNK_SIZE*chunkPos.y));
}

void Chunk::render(){
	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
}
