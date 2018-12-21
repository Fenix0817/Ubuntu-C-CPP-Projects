/*
 * square.h
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include "VertexArray.h"
#include "VertexBuffer.h"

extern gl::VertexArray* vao;

void initSquare();
void renderSquare();
void deleteSquare();

#endif /* SQUARE_H_ */
