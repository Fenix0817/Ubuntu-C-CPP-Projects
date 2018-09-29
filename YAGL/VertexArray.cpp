/*
 * VertexArray.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "VertexArray.h"

namespace gl {

VertexArray::VertexArray() {
	// TODO Auto-generated constructor stub

}

VertexArray::~VertexArray() {
	// TODO Auto-generated destructor stub
}

bool VertexArray::isCreated(){
	return id!=-1;
}

void VertexArray::create(){
	glGenVertexArrays(1,&id);
}
void VertexArray::bind(){
	glBindVertexArray(id);
}
void VertexArray::unbind(){
	glBindVertexArray(0);
}

void VertexArray::del(){
	glDeleteVertexArrays(1,&id);
	id=-1;
}

} /* namespace gl */
