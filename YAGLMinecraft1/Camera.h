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

#include "utils.h"

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
