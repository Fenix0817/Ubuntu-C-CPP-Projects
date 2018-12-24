/*
 * Scene.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#include "Scene.h"

Scene::Scene() {
	// TODO Auto-generated constructor stub

}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::init(){
	Box top;
	top.init(-2,4,-2, 4,0.5,4);
	boxes.push_back(top);

	Box side1;
	side1.init(2,0,-2, 0.5,4,4);
	boxes.push_back(side1);

	Box side2;
	side2.init(-2,0,-2, -0.5,4,4);
	boxes.push_back(side2);

	Rect floor;
	floor.init(-5,0,-5, 10,0,0, 0,0,10);
	rects.push_back(floor);

	shaderUV.create();
	shaderUV.attachFile("Shaders/display_uv.frag",gl::ShaderType::Fragment);
	attachDefaultVertexShader(shaderUV);
	shaderUV.link();

	shaderNormUV.create();
	shaderNormUV.attachFile("Shaders/norm_uv.frag",gl::ShaderType::Fragment);
	attachDefaultVertexShader(shaderNormUV);
	shaderNormUV.link();

	shaderCheckers.create();
	shaderCheckers.attachFile("Shaders/checker.frag",gl::ShaderType::Fragment);
	attachDefaultVertexShader(shaderCheckers);
	shaderCheckers.link();
}

void Scene::render(Camera cam){
	render(cam.getPerspectiveViewMatrix());
}

void Scene::render(glm::mat4 mvp){
	gl::Shader shader=shaderUV;

	shader.bind();
	shader.setMat4("MVP",mvp);

	shader.setFloat("uvScale",1);
	shader.setVec3("checkerLight",1.0,0.7,0.7);
	shader.setVec3("checkerDark" ,1.0,0.5,0.5);

	for(Box b:boxes)b.render();
	for(Rect r:rects)r.render();

	shader.unbind();
}
