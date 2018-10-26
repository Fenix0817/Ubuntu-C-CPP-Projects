/*
 * Tile.h
 *
 *  Created on: Oct 24, 2018
 *      Author: jack
 */

#ifndef TILE_H_
#define TILE_H_

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

struct Tile {
	gl::VertexArray vao;
	gl::VertexBuffer vbo;
	int sx;
	int sy;
	int sw;
	int sh;
	int sheetW;
	int sheetH;
};

gl::Shader* createTileShader();
void destroyTileShader(gl::Shader*shader);

gl::Texture createTileTexture(const char*texName);
void destroyTileTexture(gl::Texture*texture);

Tile* createTile(int spriteX,int spriteY,int spriteW,int spriteH,int sheetW,int sheetH);
void renderTile(Tile*tile,gl::Shader*shader,gl::Texture*texture,int tileX,int tileY,int gridW,int gridH);
void destroyTile(Tile*tile);

#endif /* TILE_H_ */
