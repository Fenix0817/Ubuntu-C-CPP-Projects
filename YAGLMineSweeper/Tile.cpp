/*
 * Tile.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: jack
 */

#include "Tile.h"

gl::Shader* createTileShader(){
	gl::Shader*shader=new gl::Shader();
	shader->create();
	shader->attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader->attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader->attachFile("Shaders/shader.geom",gl::ShaderType::Geometry);
	shader->link();
	return shader;
}
void destroyTileShader(gl::Shader*shader){
	shader->del();
}

gl::Texture createTileTexture(const char*texName){
	return gl::loadTexture(texName);
}

void destroyTileTexture(gl::Texture*texture){
	texture->del();
}

Tile* createTile(int spriteX,int spriteY,int spriteW,int spriteH,int sheetW,int sheetH){
	Tile* tile=new Tile();
	tile->sx=spriteX;
	tile->sy=spriteY;
	tile->sw=spriteW;
	tile->sh=spriteH;
	tile->sheetW=sheetW;
	tile->sheetH=sheetH;

	tile->vao.create();
	tile->vao.bind();
	tile->vbo.setTarget(gl::VertexBufferTarget::Array);
	tile->vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	tile->vbo.setType(gl::Type::Float);
	tile->vbo.create();
	tile->vbo.bind();
	tile->vbo.setData(sizeof(float)*2,new float[2]{0,0});
	tile->vbo.addVertexAttrib(0,2,false,2,(const GLvoid*)0);
	tile->vao.unbind();

	return tile;
}
void renderTile(Tile*tile,gl::Shader*shader,gl::Texture*texture,int tileX,int tileY,int gridW,int gridH){
	shader->bind();
	shader->setFloat("tileX",tileX);
	shader->setFloat("tileY",tileY);
	shader->setFloat("gridW",gridW);
	shader->setFloat("gridH",gridH);
	shader->setFloat("spriteX",tile->sx);
	shader->setFloat("spriteY",tile->sy);
	shader->setFloat("spriteW",tile->sw);
	shader->setFloat("spriteH",tile->sh);
	shader->setFloat("sheetW",tile->sheetW);
	shader->setFloat("sheetH",tile->sheetH);
	shader->setInt("tex",0);
	texture->bindToUnit(0);
	tile->vao.bind();
	glDrawArrays(GL_POINTS,0,1);
	tile->vao.unbind();
	shader->unbind();
}
void destroyTile(Tile*tile){
	tile->vao.del();
	tile->vbo.del();
}
