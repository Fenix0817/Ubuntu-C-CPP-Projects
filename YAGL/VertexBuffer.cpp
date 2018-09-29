/*
 * VertexBuffer.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */

#include "VertexBuffer.h"

namespace gl {

namespace VertexBufferTarget {

GLuint vertex_buffer_target_enum_to_int(vertex_buffer_target_enum vbte){
	if(vbte==Array)return GL_ARRAY_BUFFER;
	if(vbte==AtomicCounter)return GL_ATOMIC_COUNTER_BUFFER;
	if(vbte==CopyRead)return GL_COPY_READ_BUFFER;
	if(vbte==CopyWrite)return GL_COPY_WRITE_BUFFER;
	if(vbte==DispatchIndirect)return GL_DISPATCH_INDIRECT_BUFFER;
	if(vbte==DrawIndirect)return GL_DRAW_INDIRECT_BUFFER;
	if(vbte==ElementArray)return GL_ELEMENT_ARRAY_BUFFER;
	if(vbte==PixelPack)return GL_PIXEL_PACK_BUFFER;
	if(vbte==PixelUnpack)return GL_PIXEL_UNPACK_BUFFER;
	if(vbte==Query)return GL_QUERY_BUFFER;
	if(vbte==ShaderStorage)return GL_SHADER_STORAGE_BUFFER;
	if(vbte==Texture)return GL_TEXTURE_BUFFER;
	if(vbte==TransformFeedback)return GL_TRANSFORM_FEEDBACK_BUFFER;
	if(vbte==Uniform)return GL_UNIFORM_BUFFER;
	return 0;
}

}

namespace VertexBufferUsage {


GLuint vertex_buffer_usage_enum_to_int(vertex_buffer_usage_enum vbue){
	if(vbue==StreamDraw)return GL_STREAM_DRAW;
	if(vbue==StreamRead)return GL_STREAM_READ;
	if(vbue==StreamCopy)return GL_STREAM_COPY;
	if(vbue==StaticDraw)return GL_STATIC_DRAW;
	if(vbue==StaticRead)return GL_STATIC_READ;
	if(vbue==StaticCopy)return GL_STATIC_COPY;
	if(vbue==DynamicDraw)return GL_DYNAMIC_DRAW;
	if(vbue==DynamicRead)return GL_DYNAMIC_READ;
	if(vbue==DynamicCopy)return GL_DYNAMIC_COPY;
	return 0;
}

}

VertexBuffer::VertexBuffer() {
	// TODO Auto-generated constructor stub

}

VertexBuffer::VertexBuffer(VertexBufferTarget::vertex_buffer_target_enum vbte,VertexBufferUsage::vertex_buffer_usage_enum vbue,Type::type_enum te){
	target=vbte;
	usage=vbue;
	type=te;
}

VertexBuffer::~VertexBuffer() {
	// TODO Auto-generated destructor stub
}

bool VertexBuffer::isCreated(){
	return id!=-1;
}

void VertexBuffer::setTarget(VertexBufferTarget::vertex_buffer_target_enum vbte){
	target=vbte;
}
void VertexBuffer::setUsage(VertexBufferUsage::vertex_buffer_usage_enum vbue){
	usage=vbue;
}
void VertexBuffer::setType(Type::type_enum te){
	type=te;
}

int VertexBuffer::getLength(){
	return size/Type::sizeOfType(type);
}

void VertexBuffer::create(){
	glGenBuffers(1,&id);
}
void VertexBuffer::bind(){
	glBindBuffer(VertexBufferTarget::vertex_buffer_target_enum_to_int(target),id);
}
void VertexBuffer::setData(size_t length,const void*data){
	size=length;
	glBufferData(VertexBufferTarget::vertex_buffer_target_enum_to_int(target),length,data,VertexBufferUsage::vertex_buffer_usage_enum_to_int(usage));
}
void VertexBuffer::addVertexAttrib(int attrib,int size,bool norm,size_t stride,const GLvoid*ptr){
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib,size,Type::type_enum_to_int(type),norm?GL_FALSE:GL_TRUE,stride*Type::sizeOfType(type),ptr);
}
void VertexBuffer::render(){
	glDrawElements(GL_TRIANGLES,size/Type::sizeOfType(type),Type::type_enum_to_int(type),0);
}
void VertexBuffer::unbind(){
	glBindBuffer(VertexBufferTarget::vertex_buffer_target_enum_to_int(target),0);
}

void VertexBuffer::del(){
	glDeleteBuffers(1,&id);
	id=-1;
}


} /* namespace gl */
