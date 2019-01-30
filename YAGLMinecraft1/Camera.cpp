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

float align(float f){
	if(f<0)return ceil(f);
	if(f==0)return 0;
	return floor(f);
}

glm::vec3 align(glm::vec3 v){
	return glm::vec3(align(v.x),align(v.y),align(v.z));
}

bool verifyMovement(ChunkManager*cm,glm::vec3 pos,glm::vec3 dir){
	pos.y-=1;
//	Intersection inters = cm->intersectWorld(pos,dir,5);
//	if(!inters.hit)return false;
//	float dist=glm::length(glm::vec3(inters.absPos())-pos);
//	return dist>0;
	Intersection inters= cm->intersectWorld(pos,align(dir),5);
	if(!inters.hit)return true;
	return inters.dist>1;
//	dir=glm::normalize(dir);
//	if(dir.y<0)dir.y=-1;
//	glm::vec3 ipos=pos+dir;
//	ipos.x=align(ipos.x);
//	ipos.y=align(ipos.y);
//	ipos.z=align(ipos.z);
//	return cm->getBlock(glm::ivec3(ipos)).empty;
}

void Camera::moveForward(ChunkManager*cm){
	if(verifyMovement(cm,camPos,getForwardMovement()))camPos+=forwardSpeed*getForwardMovement();
}
void Camera::moveLeft(ChunkManager*cm){
	if(verifyMovement(cm,camPos,-getRightMovement()))camPos-=sideSpeed*getRightMovement();
}
void Camera::moveRight(ChunkManager*cm){
	if(verifyMovement(cm,camPos,getRightMovement()))camPos+=sideSpeed*getRightMovement();
}
void Camera::moveBack(ChunkManager*cm){
	if(verifyMovement(cm,camPos,-getForwardMovement()))camPos-=backSpeed*getForwardMovement();
}
void Camera::moveDown(ChunkManager*cm){
	if(verifyMovement(cm,camPos,glm::vec3(0,-1,0)))camPos.y-=0.1;
}
void Camera::moveUp(ChunkManager*cm){
	if(verifyMovement(cm,camPos,glm::vec3(0,1,0)))camPos.y+=0.3;
}
void Camera::jump(ChunkManager*cm){
	if(!verifyMovement(cm,camPos,glm::vec3(0,-1,0)))jumpVelocity+=.3;
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
	if(verifyMovement(cm,camPos,glm::vec3(0,sign,0))){
		camPos.y+=getVelocity();
	}

	if(verifyMovement(cm,camPos,glm::vec3(0,-1,0))){
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

	printf("mouse rotX,rotY=%f,%f  dx,dy=%f,%f\n",rotX,rotY,dx,dy);

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
	return glm::perspective(glm::radians(fovy),1.0f*windowW/windowH,0.01f,1000.0f);
}
glm::mat4 Camera::getViewMatrix(){
	return glm::lookAt(camPos,camPos+camDir,glm::vec3(0,1,0));
}
glm::mat4 Camera::getPerspectiveViewMatrix(){
	return getPerspectiveMatrix()*getViewMatrix();
}
