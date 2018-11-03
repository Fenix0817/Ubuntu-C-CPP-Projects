/*
 * main.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "Shader.h"
#include "Texture.h"

#include "Tile.h"
#include "Game.h"

int main(){
	int w=100;
	int h=100;
	int num=800;
	int size=10;

	gl::init();

	gl::Window window;
	window.create();
	window.setSize(w*size,h*size);
	window.setTitle("Minesweeper");

	window.bind();

	gl::Shader*shader=createTileShader();
	gl::Texture texture=createTileTexture("Textures/spritesheet.gif");
	texture.bind();
//	texture.setParam(gl::TextureParamName::MagFilter,gl::TextureParamValue::Linear);
	texture.unbind();

	Tile*warnings[9];
	for(int i=0;i<9;i++){
		warnings[i]=createTile(16*i,52, 16,16,  144,91);
	}
	Tile*unrevealed=createTile(0,36, 16,16,  144,91);
	Tile*flag=createTile(16,36, 16,16, 144,91);

	int numMines=num;

	Game game;
	game.initBoard(w,h);

	bool pressed=false;

	window.unbind();

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(0.5);
		gl::clearScreen();
		gl::defaultViewport(window);

		glm::vec2 pos=window.getMouse();
		int tileX=(int)(pos.x/game.getTileWidth(window.width));
		int tileY=(int)(pos.y/game.getTileHeight(window.height));
		bool mousePressed=window.mouseLeftPressed;

		for(int x=0;x<game.gw;x++){
			for(int y=0;y<game.gh;y++){
				bool b_revealed=game.revealed[x][y];
				bool b_mouse=(x==tileX&&y==tileY);
				bool b_flagged=game.flagged[x][y];
				Tile*tile=unrevealed;
				if(b_flagged&&!b_revealed)tile=flag;
				if(b_mouse&&!b_revealed&&!b_flagged&&mousePressed)tile=warnings[0];
				if(b_revealed&&!b_flagged)tile=warnings[game.getNear(x,y)];
				renderTile(tile,shader,&texture,x,y,game.gw,game.gh);
			}
		}
		if(pos.x>=0&&pos.y>=0&&pos.x<window.width&&pos.y<window.height){
			if(window.mouseLeftJustReleased){
				if(pressed){
					if(game.revealed[tileX][tileY]){
						int revealedNear=game.getRevealedNear(tileX,tileY);
						int near=game.getNear(tileX,tileY);
						int flaggedNear=game.getFlaggedNear(tileX,tileY);
						if(flaggedNear==near){
							for(int i=-1;i<=1;i++){
								for(int j=-1;j<=1;j++){
									int rx=tileX+i;
									int ry=tileY+j;
									if(rx>=0&&ry>=0&&rx<game.gw&&ry<game.gh){
										game.reveal(rx,ry);
									}
								}
							}
						}
					}
					game.reveal(tileX,tileY);
				}else{
					game.placeMines(numMines,tileX,tileY);
					game.reveal(tileX,tileY);
					pressed=true;
				}
			}
			if(window.mouseRightJustReleased){
				game.flag(tileX,tileY);
			}
		}

		window.clearInputs();
		window.unbind();
	}

	window.bind();
	for(int i=0;i<9;i++)destroyTile(warnings[i]);
	window.unbind();

	game.free();

	gl::end();
	return 0;
}
