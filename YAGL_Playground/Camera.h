/*
 * Camera.h
 *
 *  Created on: Sep 16, 2018
 *      Author: jack
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

inline float lerp(float t,float a,float b){return a+(b-a)*t;}
inline float norm(float t,float a,float b){return (b-t)/(b-a);}
inline float map(float t,float s1,float e1,float s2,float e2){return lerp(norm(t,s1,e1),s2,e2);}

#define PI 3.14159265359

class Camera {
public:
	Camera();
	virtual ~Camera();

	float fovy;
	float windowW;
	float windowH;

	float rotX=0;
	float rotY=0;

	glm::vec3 camPos;
	glm::vec3 camDir;

	glm::vec2 mouse;

	float forwardSpeed;
	float sideSpeed;
	float backSpeed;

	void moveForward();
	void moveLeft();
	void moveRight();
	void moveBack();

	void updateDirection(glm::vec2 newMouse);

	glm::vec3 getForward();
	glm::vec3 getForwardMovement();
	glm::vec3 getRightMovement();

	glm::mat4 getPerspectiveMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getPerspectiveViewMatrix();
};

#endif /* CAMERA_H_ */
