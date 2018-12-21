/*
 * square_shader.h
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#ifndef SQUARE_SHADER_H_
#define SQUARE_SHADER_H_

#include "Shader.h"

class square_shader {
public:
	square_shader(std::string fn);
	virtual ~square_shader();

	gl::Shader s;

	void render(float x,float y,float w,float h);
	void setVec3(std::string n,float x,float y,float z);
	void setInt(std::string n,int i);
};

#endif /* SQUARE_SHADER_H_ */
