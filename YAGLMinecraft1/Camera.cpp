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


void Camera::moveForward(){
	camPos+=forwardSpeed*getForwardMovement();
}
void Camera::moveLeft(){
	camPos-=sideSpeed*getRightMovement();
}
void Camera::moveRight(){
	camPos+=sideSpeed*getRightMovement();
}
void Camera::moveBack(){
	camPos-=backSpeed*getForwardMovement();
}

void Camera::updateDirection(glm::vec2 newMouse){

	glm::vec2 diff=newMouse-mouse;
	mouse=newMouse;


	float dx=map(diff.y,-10,10,-PI*0.5,PI*0.5);
	float dy=map(diff.x,-10,10,-PI,PI);

	rotX+=0.01*dx;
	rotY+=0.01*dy;

	if(rotX<-PI*0.4)rotX=-PI*0.4;
	if(rotX> PI*0.4)rotX= PI*0.4;

//	printf("%f,%f %f,%f %f,%f\n",diff.x,diff.y,rotX,rotY,dx,dy);

	camDir=glm::vec3(0,0,1);
	camDir=glm::rotateX(camDir,rotX);
	camDir=glm::rotateY(camDir,rotY);
}

glm::vec3 Camera::getForward(){
	return camDir;
}
glm::vec3 Camera::getForwardMovement(){
	return glm::normalize(glm::vec3(camDir.x,0,camDir.z));
}
glm::vec3 Camera::getRightMovement(){
	return glm::rotateY(getForwardMovement(),glm::radians(90.0f));
}

glm::mat4 Camera::getPerspectiveMatrix(){
	return glm::perspective(fovy,1.0f*windowW/windowH,0.01f,1000.0f);
}
glm::mat4 Camera::getViewMatrix(){
	return glm::lookAt(camPos,camPos+camDir,glm::vec3(0,1,0));
}
glm::mat4 Camera::getPerspectiveViewMatrix(){
	return getPerspectiveMatrix()*getViewMatrix();
}
