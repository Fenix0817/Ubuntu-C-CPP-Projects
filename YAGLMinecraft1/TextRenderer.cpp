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
//	assert(glGetError()==GL_NO_ERROR);
//	tex=gl::loadTexture("Assets/crosshair.png");
//	printf("Text atlas: \"%s\"\n",atlas->getFile().c_str());

	shader.create();
	shader.attachFile("Shaders/text.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/text.frag",gl::ShaderType::Fragment);
	shader.link();

	float posData[]={
			-1,-1,
			-1, 1,
			 1, 1,
			 1,-1
	};

	float uvData[]={
			0,0,
			0,1,
			1,1,
			1,0
	};

	unsigned int triData[]={
			0,1,2,
			0,2,3
	};


	vao.create();
	vao.bind();

	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.addVertexAttrib(0,2,false,2,(const GLvoid*)0);
	vboPos.setData(sizeof(posData),posData);
	vboPos.unbind();

	vboUV.setTarget(gl::VertexBufferTarget::Array);
	vboUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboUV.setType(gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.addVertexAttrib(1,2,false,2,(const GLvoid*)0);
	vboUV.setData(sizeof(uvData),uvData);
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

	std::vector<float>posData;
	std::vector<float>uvData;
	std::vector<unsigned int>triData;

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

		posData.push_back(x*w);
		posData.push_back(y*h);

		posData.push_back((x+1)*w);
		posData.push_back(y*h);

		posData.push_back((x+1)*w);
		posData.push_back((y+1)*h);

		posData.push_back(x*w);
		posData.push_back((y+1)*h);

		uvData.push_back(pos.x);
		uvData.push_back(pos.y);

		uvData.push_back(pos.x+pos.w);
		uvData.push_back(pos.y);

		uvData.push_back(pos.x+pos.w);
		uvData.push_back(pos.y+pos.h);

		uvData.push_back(pos.x);
		uvData.push_back(pos.y+pos.h);

		triData.push_back(numCharsSoFar*4+0);
		triData.push_back(numCharsSoFar*4+1);
		triData.push_back(numCharsSoFar*4+2);
		triData.push_back(numCharsSoFar*4+0);
		triData.push_back(numCharsSoFar*4+3);
		triData.push_back(numCharsSoFar*4+2);

//		posData[i_p]=x*w;i_p++;
//		posData[i_p]=y*h;i_p++;
//
//		posData[i_p]=(x+1)*w;i_p++;
//		posData[i_p]=y*h;i_p++;
//
//		posData[i_p]=(x+1)*w;i_p++;
//		posData[i_p]=(y+1)*h;i_p++;
//
//		posData[i_p]=x*w;i_p++;
//		posData[i_p]=(y+1)*h;i_p++;
//
//
//		uvData[i_u]=pos.x;i_u++;
//		uvData[i_u]=pos.y+pos.h;i_u++;
//
//		uvData[i_u]=pos.x+pos.w;i_u++;
//		uvData[i_u]=pos.y+pos.h;i_u++;
//
//		uvData[i_u]=pos.x+pos.w;i_u++;
//		uvData[i_u]=pos.y;i_u++;
//
//		uvData[i_u]=pos.x;i_u++;
//		uvData[i_u]=pos.y;i_u++;
//
//
//		triData[i_t]=numCharsSoFar*4+0;i_t++;
//		triData[i_t]=numCharsSoFar*4+1;i_t++;
//		triData[i_t]=numCharsSoFar*4+2;i_t++;
//		triData[i_t]=numCharsSoFar*4+0;i_t++;
//		triData[i_t]=numCharsSoFar*4+3;i_t++;
//		triData[i_t]=numCharsSoFar*4+2;i_t++;

		x++;
		numCharsSoFar++;
	}

	vao.bind();
	vboPos.bind();
	vboPos.setData(sizeof(float)*posData.size(),posData.data());
	vboPos.unbind();
	vboUV.bind();
	vboUV.setData(sizeof(uvData)*uvData.size(),uvData.data());
	vboUV.unbind();
	ebo.bind();
	ebo.setData(sizeof(unsigned int)*triData.size(),triData.data());
	ebo.unbind();
	vao.unbind();

}
void TextRenderer::render(float x,float y,float size){
	shader.bind();
//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

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
	shader.unbind();
}



















