/*
 * Box.h
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#ifndef BOX_H_
#define BOX_H_

#include "VertexArray.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>

class Box {
public:
	Box();
	virtual ~Box();

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboUV;
	gl::VertexBuffer vboNormUV;
	gl::VertexBuffer ebo;

	float x;
	float y;
	float z;
	float sx;
	float sy;
	float sz;

	inline glm::vec3 pos(){return glm::vec3(x,y,z);}
	inline glm::vec3 size(){return glm::vec3(sx,sy,sz);}

	void init(float x,float y,float z,float sx,float sy,float sz);
	void render();
};

#endif /* BOX_H_ */
