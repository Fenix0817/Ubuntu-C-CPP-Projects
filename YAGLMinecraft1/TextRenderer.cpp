/*
 * TextRenderer.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#include "TextRenderer.h"

TextRenderer::TextRenderer() {
	// TODO Auto-generated constructor stub

}

TextRenderer::~TextRenderer() {
	// TODO Auto-generated destructor stub
}

void TextRenderer::init(){
	tex=gl::loadTexture(atlas->getFile());
	printf("Text atlas: %s\n",atlas->getFile().c_str());

	shader.create();
	shader.attachFile("Shaders/text.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/text.frag",gl::ShaderType::Fragment);
	shader.link();

	float posData[]={};
	float uvData[]={};
	unsigned int triData[]={};

	vao.create();
	vao.bind();

	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.addVertexAttrib(0,2,false,2,(const GLvoid*)0);
	vboPos.unbind();

	vboUV.setTarget(gl::VertexBufferTarget::Array);
	vboUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboUV.setType(gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.addVertexAttrib(1,2,false,2,(const GLvoid*)0);
	vboUV.unbind();

	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();
}
void TextRenderer::setText(std::string txt){

	int numChars=txt.size();

	float posData[8*numChars];
	float uvData[8*numChars];
	unsigned int triData[6*numChars];

	int i_p=0;
	int i_u=0;
	int i_t=0;
	int x=0;
	int y=-1;
	int numCharsSoFar=0;

	float aspect=atlas->getAspectRatio();
	float w=aspect;
	float h=1;

	for(int i=0;i<numChars;i++){
		char c=txt[i];
		TextAtlasPos pos=atlas->getPos(c);
		if(c=='\n'){
			x=0;
			y--;
			continue;
		}

		posData[i_p]=x*w;i_p++;
		posData[i_p]=y*h;i_p++;

		posData[i_p]=(x+1)*w;i_p++;
		posData[i_p]=y*h;i_p++;

		posData[i_p]=(x+1)*w;i_p++;
		posData[i_p]=(y+1)*h;i_p++;

		posData[i_p]=x*w;i_p++;
		posData[i_p]=(y+1)*h;i_p++;


		uvData[i_u]=pos.x;i_u++;
		uvData[i_u]=pos.y+pos.h;i_u++;

		uvData[i_u]=pos.x+pos.w;i_u++;
		uvData[i_u]=pos.y+pos.h;i_u++;

		uvData[i_u]=pos.x+pos.w;i_u++;
		uvData[i_u]=pos.y;i_u++;

		uvData[i_u]=pos.x;i_u++;
		uvData[i_u]=pos.y;i_u++;


		triData[i_t]=numCharsSoFar*4+0;i_t++;
		triData[i_t]=numCharsSoFar*4+1;i_t++;
		triData[i_t]=numCharsSoFar*4+2;i_t++;
		triData[i_t]=numCharsSoFar*4+0;i_t++;
		triData[i_t]=numCharsSoFar*4+3;i_t++;
		triData[i_t]=numCharsSoFar*4+2;i_t++;

		x++;
		numCharsSoFar++;
	}

	vao.bind();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.unbind();
	vboUV.bind();
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.unbind();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();
	vao.unbind();

}
void TextRenderer::render(float x,float y,float size){
	shader.bind();
	tex.bindToUnit(0);
	shader.setInt("tex",0);
	shader.setMat4("matrix", glm::translate(glm::mat4(1),glm::vec3(x,y,0))*glm::scale(glm::mat4(1),glm::vec3(size,size,0)));
//	shader.setMat4("matrix",glm::mat4(
//			1/size,0,0,-x,
//			0,1/size,0,-y,
//			0,0,1/size,0,
//			0,0,0,1
//	));
	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
}



















