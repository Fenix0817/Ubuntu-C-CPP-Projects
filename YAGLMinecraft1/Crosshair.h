/*
 * Crosshair.h
 *
 *  Created on: Nov 23, 2018
 *      Author: jack
 */

#ifndef CROSSHAIR_H_
#define CROSSHAIR_H_

#include <YAGL.h>

class Crosshair {
public:
	Crosshair();
	virtual ~Crosshair();

	gl::Shader shader;
	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboUV;
	gl::VertexBuffer ebo;
	gl::Texture tex;

	void init();
	void render();

};

#endif /* CROSSHAIR_H_ */
