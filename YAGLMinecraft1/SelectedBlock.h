/*
 * SelectedBlock.h
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#ifndef SELECTEDBLOCK_H_
#define SELECTEDBLOCK_H_

#include <YAGL.h>
#include "Camera.h"

class SelectedBlock {
public:
	SelectedBlock();
	virtual ~SelectedBlock();

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboUV;
	gl::VertexBuffer ebo;

	gl::Shader shader;

	void init();
	void render(float x,float y,float z,Camera cam);
};

#endif /* SELECTEDBLOCK_H_ */
