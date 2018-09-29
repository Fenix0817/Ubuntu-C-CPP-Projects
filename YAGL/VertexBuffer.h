/*
 * VertexBuffer.h
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Utilities.h"

namespace gl {

namespace VertexBufferTarget {

enum vertex_buffer_target_enum {
	Array,
	AtomicCounter,
	CopyRead,
	CopyWrite,
	DispatchIndirect,
	DrawIndirect,
	ElementArray,
	PixelPack,
	PixelUnpack,
	Query,
	ShaderStorage,
	Texture,
	TransformFeedback,
	Uniform
};

GLuint vertex_buffer_target_enum_to_int(vertex_buffer_target_enum vbte);

}

namespace VertexBufferUsage {

enum vertex_buffer_usage_enum {
	StreamDraw,
	StreamRead,
	StreamCopy,
	StaticDraw,
	StaticRead,
	StaticCopy,
	DynamicDraw,
	DynamicRead,
	DynamicCopy
};

GLuint vertex_buffer_usage_enum_to_int(vertex_buffer_usage_enum vbue);

}

class VertexBuffer {
public:
	VertexBuffer();
	VertexBuffer(VertexBufferTarget::vertex_buffer_target_enum vbte,VertexBufferUsage::vertex_buffer_usage_enum vbue,Type::type_enum te);
	virtual ~VertexBuffer();

	GLuint id=-1;
	VertexBufferTarget::vertex_buffer_target_enum target;
	VertexBufferUsage::vertex_buffer_usage_enum usage;
	Type::type_enum type;
	size_t size;

	bool isCreated();

	int getLength();

	void setTarget(VertexBufferTarget::vertex_buffer_target_enum vbte);
	void setUsage(VertexBufferUsage::vertex_buffer_usage_enum vbue);
	void setType(Type::type_enum te);

	void create();
	void bind();
	void setData(size_t length,const void*data);
	void addVertexAttrib(int attrib,int size,bool norm,size_t stride,const GLvoid*ptr);
	void render();
	void unbind();

	void del();

};

} /* namespace gl */

#endif /* VERTEXBUFFER_H_ */
