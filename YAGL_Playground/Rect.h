/*
 * Rect.h
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#ifndef RECT_H_
#define RECT_H_

#include "VertexArray.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>

class Rect {
public:
	Rect();
	virtual ~Rect();

	gl::VertexArray vao;
	gl::VertexBuffer vboPos;
	gl::VertexBuffer vboUV;
	gl::VertexBuffer vboNormUV;
	gl::VertexBuffer ebo;

	float x;
	float y;
	float z;
	float ax;
	float ay;
	float az;
	float bx;
	float by;
	float bz;

	inline glm::vec3 pos(){return glm::vec3(x,y,z);}
	inline glm::vec3 a(){return glm::vec3(ax,ay,az);}
	inline glm::vec3 b(){return glm::vec3(bx,by,bz);}

	void init(float x,float y,float z,float ax,float ay,float az,float bx,float by,float bz);
	void render();

	glm::vec3 intersect(glm::vec3 ro,glm::vec3 rd);
};

#endif /* RECT_H_ */
