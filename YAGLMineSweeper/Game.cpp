/*
 * Game.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: jack
 */

#include "Game.h"

Game::Game() {
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

bool Game::inBounds(int x,int y){
	return x>=0&&y>=0&&x<gw&&y<gh;
}

bool Game::getBomb(int x,int y){
	if(inBounds(x,y))return bombs[x][y];
	return false;
}

int Game::getNear(int x,int y){
	return getBomb(x-1,y-1)+getBomb(x-1,y)+getBomb(x-1,y+1)+getBomb(x,y-1)+getBomb(x,y+1)+getBomb(x+1,y-1)+getBomb(x+1,y)+getBomb(x+1,y+1);
}

int Game::getRevealedNear(int x,int y){
	int n=0;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int rx=x+i;
			int ry=y+j;
			if(rx<0||ry<0||rx>=gw||ry>=gh)continue;
			if(revealed[rx][ry])n++;
		}
	}
	return n;
}

int Game::getFlaggedNear(int x,int y){
	int n=0;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int rx=x+i;
			int ry=y+j;
			if(rx<0||ry<0||rx>=gw||ry>=gh)continue;
			if(flagged[rx][ry])n++;
		}
	}
	return n;
}

void Game::initBoard(int w,int h){
	numBombs=0;
	gw=w;
	gh=h;
	bombs=new bool*[gw];
	revealed=new bool*[gw];
	flagged=new bool*[gw];
	for(int x=0;x<gw;x++){
		bombs[x]=new bool[gh];
		revealed[x]=new bool[gh];
		flagged[x]=new bool[gh];
		for(int y=0;y<gh;y++){
			bombs[x][y]=false;
			revealed[x][y]=false;
			flagged[x][y]=false;
		}
	}
	printf("Board initialized with size %ix%i\n",gw,gh);
}

void Game::placeMines(int numMines,int safeX,int safeY){
	std::vector<int>xCoords;
	std::vector<int>yCoords;
	for(int x=0;x<gw;x++){
		for(int y=0;y<gh;y++){
			bool near=abs(safeX-x)<=1&&abs(safeY-y)<=1;
			if(!near){
				xCoords.push_back(x);
				yCoords.push_back(y);
			}
		}
	}
	int i=0;
	while(xCoords.size()>0&&i<numMines){
		i++;
		int ind=rand()%xCoords.size();
		int x=xCoords[ind];
		int y=yCoords[ind];
		bombs[x][y]=true;
		xCoords.erase(xCoords.begin()+x);
		yCoords.erase(yCoords.begin()+y);
	}
}

void Game::flag(int x,int y){
	flagged[x][y]=!flagged[x][y];
}
void Game::reveal(int x,int y){
	printf("Reveal %i,%i\n",x,y);
	if(!inBounds(x,y))return;
	printf("In bounds at %i,%i\n",x,y);
	if(revealed[x][y])return;
	printf("Not revealed at %i,%i\n",x,y);
	if(bombs[x][y])return;
	revealed[x][y]=true;
	if(getNear(x,y)!=0)return;
	reveal(x-1,y-1);
	reveal(x-1,y);
	reveal(x-1,y+1);
	reveal(x,y-1);
	reveal(x,y+1);
	reveal(x+1,y-1);
	reveal(x+1,y);
	reveal(x+1,y+1);
}

int Game::getTileWidth(int w){
	return w/gw;
}
int Game::getTileHeight(int h){
	return h/gh;
}

void Game::free(){
	for(int x=0;x<gw;x++){
		delete[]bombs[x];
		delete[]revealed[x];
		delete[]flagged[x];
	}
	delete[]bombs;
	delete[]revealed;
	delete[]flagged;
}
