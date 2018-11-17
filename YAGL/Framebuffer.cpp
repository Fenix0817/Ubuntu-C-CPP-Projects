/*
 * Framebuffer.cpp
 *
 *  Created on: Nov 17, 2018
 *      Author: jack
 */

#include <Framebuffer.h>

namespace gl {

Framebuffer::Framebuffer() {
	// TODO Auto-generated constructor stub

}

Framebuffer::~Framebuffer() {
	// TODO Auto-generated destructor stub
}

void Framebuffer::create(){
	glGenFramebuffers(1,&id);
}
bool Framebuffer::complete(){
	return glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE;
}
void Framebuffer::bind(){
	glBindFramebuffer(GL_FRAMEBUFFER,id);
}
void Framebuffer::unbind(){
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}
void Framebuffer::attach(Texture t,FBOAttachment a){
	if(t.target!=TextureTarget::Tex2D){
		printf("Cannot attach a texture with a target that is not TextureTarget::Tex2D.\n");
		printf("Exiting.\n");
		exit(EXIT_FAILURE);
	}
	glFramebufferTexture2D(GL_FRAMEBUFFER,a,GL_TEXTURE_2D,t.id,0);
}
void Framebuffer::del(){
	glDeleteFramebuffers(1,&id);
}

} /* namespace gl */
