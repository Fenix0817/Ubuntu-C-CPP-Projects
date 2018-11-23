/*
 * TextRenderer.h
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#ifndef TEXTRENDERER_H_
#define TEXTRENDERER_H_

#include "TextAtlasPos.h"
#include "TextAtlas.h"
#include <YAGL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Taken from my LWJGL framework
//https://github.com/mackycheese/eclipse-workspace/blob/master/GLFrameworkLWJGL/src/co/megadodo/lwjgl/glframework/text/TextRenderer.java
class TextRenderer {
public:
	TextRenderer();
	virtual ~TextRenderer();

	gl::Shader shader;
	gl::VertexArray vao;
	gl::VertexBuffer vboPos,vboUV,ebo;
	gl::Texture tex;
	TextAtlas*atlas;

	void init();
	void setText(std::string txt);
	void render(float x,float y,float size);
};

#endif /* TEXTRENDERER_H_ */
