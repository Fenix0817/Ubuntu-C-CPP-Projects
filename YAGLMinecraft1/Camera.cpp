/*
 * Camera.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#include "Camera.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub

}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


int align(float p,float d){
	return floor(p);
}

glm::ivec3 align(glm::vec3 pos,glm::vec3 dir){
	return glm::vec3(align(pos.x,dir.x),align(pos.y,dir.y),align(pos.z,dir.z));
}

int norm(float f){
	if(f>0)return 1;
	if(f<0)return -1;
	return 0;
}

glm::ivec3 norm(glm::vec3 d){
	return glm::ivec3(norm(d.x),norm(d.y),norm(d.z));
}

bool basicVerify(ChunkManager*cm,glm::vec3 p){
//	return cm->getBlock(p.x,p.y,p.z).empty;
	glm::ivec3 mi=glm::floor(p);
	glm::ivec3 ma=glm::floor(p+glm::vec3(0,CAM_ELEV,0));
//	ma.y=ceil(p.y+1);
	for(int x=mi.x;x<=ma.x;x++){
		for(int y=mi.y;y<=ma.y;y++){
			for(int z=mi.z;z<=ma.z;z++){
				if(!cm->getBlock(x,y,z).empty)return false;
			}
		}
	}
	return true;
}

glm::vec3 verifyMovementBasic(ChunkManager*cm,glm::vec3 pos,glm::vec3 dir){
//	glm::ivec3 i=align(pos,dir);

	if(dir==glm::vec3(0,0,0))return dir;
	glm::vec3 res=dir;

	glm::ivec3 normDir=norm(dir);

	if(!basicVerify(cm,pos+glm::vec3(dir.x,0,0)))res.x=0;
	if(!basicVerify(cm,pos+glm::vec3(0,dir.y,0)))res.y=0;
	if(!basicVerify(cm,pos+glm::vec3(0,0,dir.z)))res.z=0;
	if(!basicVerify(cm,pos))res=glm::vec3(0,0,0);


	return res;
}

glm::vec3 verifyMovement(ChunkManager*cm,glm::vec3 pos,glm::vec3 dir){
	glm::vec3 v0 = verifyMovementBasic(cm,pos-glm::vec3(0,0,0),dir);
	glm::vec3 v1 = verifyMovementBasic(cm,pos-glm::vec3(0,CAM_ELEV,0),dir);
	if(v1.x==0)v0.x=0;
	if(v1.y==0)v0.y=0;
	if(v1.z==0)v0.z=0;
	return v0;
}

void Camera::moveForward(ChunkManager*cm){
//	if(verifyMovement(cm,camPos,getForwardMovement()))camPos+=forwardSpeed*getForwardMovement();
	camPos+=verifyMovement(cm,camPos,forwardSpeed*getForwardMovement());
}
void Camera::moveLeft(ChunkManager*cm){
	camPos+=verifyMovement(cm,camPos,-sideSpeed*getRightMovement());
}
void Camera::moveRight(ChunkManager*cm){
	camPos+=verifyMovement(cm,camPos,sideSpeed*getRightMovement());
}
void Camera::moveBack(ChunkManager*cm){
	camPos+=verifyMovement(cm,camPos,-backSpeed*getForwardMovement());
}
void Camera::moveDown(ChunkManager*cm){
//	if(verifyMovement(cm,camPos,glm::vec3(0,-1,0)))camPos.y-=0.1;
	camPos-=0.1f*verifyMovement(cm,camPos,glm::vec3(0,-1,0));
}
void Camera::moveUp(ChunkManager*cm){
//	if(verifyMovement(cm,camPos,glm::vec3(0,1,0)))camPos.y+=0.3;
	camPos+=0.3f*verifyMovement(cm,camPos,glm::vec3(0,1,0));
}
void Camera::jump(ChunkManager*cm){
//	if(!verifyMovement(cm,camPos,glm::vec3(0,-1,0)))jumpVelocity+=.3;
	if(verifyMovement(cm,camPos,glm::vec3(0,-1,0))==glm::vec3(0,0,0))jumpVelocity+=0.1;
}
float Camera::getVelocity(){
	return jumpVelocity+gravityVelocity;
}
void Camera::applyGravity(ChunkManager*cm){
	//Fix jumping
	//The issue is verifyMovement(up) returns false
	//Why?
	//Is it a "non-intersection returns false" issue?
	int sign=-1;
	if(getVelocity()>0)sign=1;
	if(verifyMovement(cm,camPos,glm::vec3(0,sign,0))!=glm::vec3(0,0,0)){
		camPos.y+=getVelocity();
	}

	if(verifyMovement(cm,camPos,glm::vec3(0,-1,0))!=glm::vec3(0,0,0)){
		gravityVelocity-=0.005;
	}else{//grounded
		jumpVelocity=0;
		gravityVelocity=0;
	}
//	if(verifyMovement(cm,camPos,glm::vec3(0,sign,0))){
//		camPos.y+=velocity;
//		velocity-=0.0025;
//	}
//	else velocity=0;
}

void Camera::updateDirection(glm::vec2 newMouse){

	glm::vec2 diff=newMouse-mouse;
	mouse=newMouse;


	float dx=map(diff.y,-10,10,PI*0.5,-PI*0.5);
	float dy=map(diff.x,-10,10,PI,-PI);

	rotX+=0.01*dx;
	rotY+=0.01*dy;

	if(rotX<-PI*0.49)rotX=-PI*0.49;
	if(rotX> PI*0.49)rotX= PI*0.49;

//	printf("%f,%f %f,%f %f,%f\n",diff.x,diff.y,rotX,rotY,dx,dy);

	camDir=glm::vec3(0,0,1);
	camDir=glm::rotateX(camDir,rotX);
	camDir=glm::rotateY(camDir,rotY);

	if(isnanf(rotX))rotX=0;
	if(isnanf(rotY))rotY=0;

	if(isnanf(camDir.x)||isnanf(camDir.y)||isnanf(camDir.z))camDir=glm::vec3(1,0,0);
}

glm::vec3 Camera::getForward(){
	return camDir;
}
glm::vec3 Camera::getForwardMovement(){
	return glm::normalize(glm::vec3(camDir.x,0,camDir.z));
}
glm::vec3 Camera::getRightMovement(){
	return glm::rotateY(getForwardMovement(),-glm::radians(90.0f));
}

glm::mat4 Camera::getPerspectiveMatrix(){
	return glm::perspective(glm::radians(fovy),1.0f*windowW/windowH,0.001f,1000.0f);
}
glm::mat4 Camera::getViewMatrix(){
	return glm::lookAt(camPos,camPos+camDir,glm::vec3(0,1,0));
}
glm::mat4 Camera::getPerspectiveViewMatrix(){
	return getPerspectiveMatrix()*getViewMatrix();
}
