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
//	if(f<0)return ceil(f);
//	if(f==0)return 0;
	return round(f);
}

glm::vec3 align(glm::vec3 v){
	return glm::vec3(align(v.x),align(v.y),align(v.z));
}

bool basicVerify(ChunkManager*cm,glm::ivec3 p){
	return cm->getBlock(p.x,p.y,p.z).empty;
}

glm::vec3 verifyMovement(ChunkManager*cm,glm::vec3 pos,glm::vec3 dir){
	pos.y-=1;
//	Intersection inters = cm->intersectWorld(pos,dir,5);
//	if(!inters.hit)return false;
//	float dist=glm::length(glm::vec3(inters.absPos())-pos);
//	return dist>0;
	glm::vec3 res=dir;

	/*
	 * TODO
	 * fix bug
	   cam position -1.943915,33.989986,37.014339
	   cam dir at -0.649753,-0.689114,-0.320847
	 * where it just lets you walk through
	 * only a problem at that y-level; same direction but lower works fine
	 */

	glm::vec3 dx=dir; dx.z=0;
	if(!basicVerify(cm,pos+dx))res.x=0;

	glm::vec3 dz=dir; dz.x=0;
	if(!basicVerify(cm,pos+dz))res.z=0;

	if(!basicVerify(cm,pos+glm::vec3(0,res.y,0)))res.y=0;

	return res;
//	pos+=dir;
//	glm::ivec3 p=glm::floor(pos);
//	for(int x=-1;x<=1;x++){
//		for(int y=-1;y<=1;y++){
//			for(int z=-1;z<=1;z++){
//				if(!cm->getBlock(x+p.x,y+p.y,z+p.z).empty){
//					return false;
//				}
//			}
//		}
//	}
//	return true;
//	return cm->getBlock(p.x,p.y,p.z).empty;
//	Intersection inters= cm->intersectWorld(align(pos),align(dir),5);
//	if(!inters.hit)return true;
//	return inters.dist>1;
//	dir=glm::normalize(dir);
//	if(dir.y<0)dir.y=-1;
//	glm::vec3 ipos=pos+dir;
//	ipos.x=align(ipos.x);
//	ipos.y=align(ipos.y);
//	ipos.z=align(ipos.z);
//	return cm->getBlock(glm::ivec3(ipos)).empty;
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
