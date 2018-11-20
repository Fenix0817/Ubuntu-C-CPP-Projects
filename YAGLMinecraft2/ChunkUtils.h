/*
 * ChunkUtils.h
 *
 *  Created on: Nov 19, 2018
 *      Author: jack
 */

#ifndef CHUNKUTILS_H_
#define CHUNKUTILS_H_

#include "VertexArray.h"
#include "VertexBuffer.h"

namespace ChunkUtils {

inline gl::VertexBuffer createStaticArrayFloatBuffer(){
	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Float);
	vbo.create();
	return vbo;
}

inline gl::VertexBuffer createStaticArrayIntBuffer(){
	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Int);
	vbo.create();
	return vbo;
}

}


#endif /* CHUNKUTILS_H_ */
