/*
 * Scene.h
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include "Box.h"
#include "Shader.h"
#include "Utils.h"
#include "Rect.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	gl::Shader shaderUV;
	gl::Shader shaderCheckers;
	gl::Shader shaderNormUV;

	std::vector<Box>boxes;
	std::vector<Rect>rects;

	void init();

	void render(Camera cam);
	void render(glm::mat4 mvp);
};

#endif /* SCENE_H_ */
