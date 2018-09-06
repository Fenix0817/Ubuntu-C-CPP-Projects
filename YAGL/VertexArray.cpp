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

void VertexArray::create(){
	glGenVertexArrays(1,&id);
}
void VertexArray::bind(){
	glBindVertexArray(id);
}
void VertexArray::unbind(){
	glBindVertexArray(0);
}

} /* namespace gl */
