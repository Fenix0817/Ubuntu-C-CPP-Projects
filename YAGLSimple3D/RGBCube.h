/*
 * RGBCube.h
 *
 *  Created on: Sep 12, 2018
 *      Author: jack
 */

#ifndef RGBCUBE_H_
#define RGBCUBE_H_

#include <glm/glm.hpp>
//#include <GLFW/glfw3.h>
//#include "glad/glad.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

class RGBCube {
public:
	RGBCube();
	virtual ~RGBCube();

	gl::Shader shader;

	gl::VertexArray vao;

	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboCol;
	gl::VertexBuffer vboNorm;
	gl::VertexBuffer ebo;

	void init();
	void render(glm::mat4 perspective,glm::mat4 view,glm::mat4 model);
};

#endif /* RGBCUBE_H_ */
