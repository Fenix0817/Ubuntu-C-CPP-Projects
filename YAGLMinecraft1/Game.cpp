/*
 * Game.cpp
 *
 *  Created on: Nov 24, 2018
 *      Author: jack
 */

#include "Game.h"

Game::Game() {
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::init() {
//	textAtlas = new TextAtlasMonospaced();
//
//	txtRenderer.atlas = textAtlas;
//	txtRenderer.init();

//	atlas = new AtlasNormal();
//	atlas = new AtlasFogleman();
	atlas = new AtlasHD();

	noise = new FastNoise();

	chunkManager.noise = noise;
	chunkManager.atlas = atlas;

	shader.create();
	shader.attachFile("Shaders/chunk.vert", gl::ShaderType::Vertex);
	shader.attachFile("Shaders/chunk.frag", gl::ShaderType::Fragment);
	shader.link();

	texture = gl::loadTexture(atlas->getFileName());
	texture.bind();
	texture.setParam(gl::TextureParamName::MinFilter,gl::TextureParamValue::Nearest);
	texture.setParam(gl::TextureParamName::MagFilter,gl::TextureParamValue::Nearest);
	texture.unbind();

	camera.camPos = glm::vec3(CHUNK_SIZE / 2, 40, CHUNK_SIZE / 2);
	camera.camDir = glm::vec3(1, 0, 0);

	camera.forwardSpeed = 0.1;
	camera.sideSpeed = 0.1;
	camera.backSpeed = 0.1;


	selectedBlock.init();

	crosshair.init();

}
void Game::loop(gl::Window window) {

	if(window.wasJustPressed('P')){
		printf("------------------------------------------------------------\n");
		printf("num chunks rendered: %i\n",chunkManager.getNumChunksRendered());
		printf("num chunks in memory: %i\n",chunkManager.getNumChunksInMemory());
		printf("cam position %f,%f,%f\n",camera.camPos.x,camera.camPos.y,camera.camPos.z);
		printf("cam dir at %f,%f,%f\n",camera.camDir.x,camera.camDir.y,camera.camDir.z);
	}
	frames++;

	prevTime=time;
	time=gl::time();

#ifdef DEBUG_FPS
	printf("SPF: %f, FPS: %f\n",time-prevTime,1/(time-prevTime));
#endif

	gl::defaultViewport(window);
	gl::setDepth(true);
	gl::setClearColor(fogR,fogG,fogB);
	gl::clearScreen();

	shader.bind();
	shader.setVec4("fogColor", fogR,fogG,fogB,1);

	texture.bindToUnit(0);
	shader.setInt("tex",0);

	camera.fovy=80;
	if(window.isKeyDown('F'))camera.fovy=20;
	camera.windowW=window.width;
	camera.windowH=window.height;

	chunkManager.render(shader,camera.getPerspectiveViewMatrix());
	shader.unbind();

	Intersection selectedIntersection=chunkManager.intersectWorld(camera.camPos,camera.camDir,50);


	if(selectedIntersection.hit){
		glm::ivec3 s=selectedIntersection.abs;
		Block hitBlock=chunkManager.getBlock(s);
		selectedBlock.render(s.x,s.y,s.z,camera);
	}

	crosshair.render();

	glm::vec2 chunkPos=getChunkCoord(glm::ivec2((int)camera.camPos.x,(int)camera.camPos.z));
	chunkManager.update(frames,chunkPos);

	glm::vec2 mouse=window.getMouse();
	camera.updateDirection(mouse);
	if(mouse.x<0||mouse.y<0||mouse.x>window.width||mouse.y>window.height)
			window.setMouse(window.width/2,window.height/2);
	mouse=window.getMouse();
	camera.mouse=mouse;

	if(window.isKeyDown('W'))camera.moveForward(&chunkManager);
	if(window.isKeyDown('S'))camera.moveBack(&chunkManager);
	if(window.isKeyDown('A'))camera.moveLeft(&chunkManager);
	if(window.isKeyDown('D'))camera.moveRight(&chunkManager);

	float jumpDiff=gl::time()-lastJumpTime;
	if(window.isKeyDown(' ')){
		camera.jump(&chunkManager);
		lastJumpTime=gl::time();
	}

//	if(window.isKeyDown(' '))camera.moveUp(&chunkManager);
//	if(window.isKeyDown(GLFW_KEY_LEFT_SHIFT))camera.moveDown(&chunkManager);
	if(window.isKeyDown(GLFW_KEY_ESCAPE)||window.isKeyDown('/'))window.close();
	camera.applyGravity(&chunkManager);
	// ABOVE - '/' is a exit key because touchbar ESCAPE sometimes doesn't work

	if(window.mouseLeftJustPressed&&selectedIntersection.hit){
		glm::ivec3 pos=selectedIntersection.abs;
		chunkManager.setBlock(pos.x,pos.y,pos.z,blockEmpty);

		glm::ivec2 c=getChunkCoord(glm::ivec2(pos.x,pos.z));
		chunkManager.remeshChunk(c.x,c.y);
		glm::ivec2 p=getPosInChunk(glm::ivec2(pos.x,pos.z));
		if(p.x==0)chunkManager.remeshChunk(c.x-1,c.y);
		if(p.y==0)chunkManager.remeshChunk(c.x,c.y-1);
		if(p.x==CHUNK_SIZE-1)chunkManager.remeshChunk(c.x+1,c.y);
		if(p.y==CHUNK_SIZE-1)chunkManager.remeshChunk(c.x,c.y+1);
	}

	if((window.mouseRightJustPressed||window.wasJustPressed('R'))&&selectedIntersection.hit){
		glm::ivec3 pos=selectedIntersection.prev;
		chunkManager.setBlock(pos.x,pos.y,pos.z,blockStone);

		glm::ivec2 c=getChunkCoord(glm::ivec2(pos.x,pos.z));
		chunkManager.remeshChunk(c.x,c.y);
		glm::ivec2 p=getPosInChunk(glm::ivec2(pos.x,pos.z));
		if(p.x==0)chunkManager.remeshChunk(c.x-1,c.y);
		if(p.y==0)chunkManager.remeshChunk(c.x,c.y-1);
		if(p.x==CHUNK_SIZE-1)chunkManager.remeshChunk(c.x+1,c.y);
		if(p.y==CHUNK_SIZE-1)chunkManager.remeshChunk(c.x,c.y+1);
	}

	if(window.isKeyDown('C')&&selectedIntersection.hit){
//		if(true){
//			int posX=(int)camera.camPos.x;
//			int posY=(int)camera.camPos.y;
//			int posZ=(int)camera.camPos.z;
		glm::ivec3 pos=selectedIntersection.abs;
		int posX=(int)pos.x;
		int posY=(int)pos.y;
		int posZ=(int)pos.z;
		int a=1;
		std::vector<glm::ivec2>changes;
		for(int x=-a;x<=a;x++){
			for(int y=-a;y<=a;y++){
				for(int z=-a;z<=a;z++){
					if(y+posY<0)continue;
					glm::ivec2 worldXZ=glm::ivec2(x+posX,z+posZ);
					glm::ivec2 chunkCoord=getChunkCoord(worldXZ);
					if(!contains_ivec2(changes,chunkCoord))changes.push_back(chunkCoord);
					if(!contains_ivec2(changes,chunkCoord+glm::ivec2(-1,0)))changes.push_back(chunkCoord+glm::ivec2(-1,0));
					if(!contains_ivec2(changes,chunkCoord+glm::ivec2( 1,0)))changes.push_back(chunkCoord+glm::ivec2( 1,0));
					if(!contains_ivec2(changes,chunkCoord+glm::ivec2(0,-1)))changes.push_back(chunkCoord+glm::ivec2(0,-1));
					if(!contains_ivec2(changes,chunkCoord+glm::ivec2(0, 1)))changes.push_back(chunkCoord+glm::ivec2(0, 1));
					chunkManager.setBlock(x+posX,y+posY,z+posZ,blockEmpty);
				}
			}
		}
		for(int i=0;i<changes.size();i++){
			chunkManager.remeshChunk(changes[i].x,changes[i].y);
		}
	}

}
