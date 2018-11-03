/*
 * ppm.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: jack
 */

#include "ppm.h"

ppm::ppm() {
	// TODO Auto-generated constructor stub

}

ppm::~ppm() {
	// TODO Auto-generated destructor stub
}


int ppm::getInd(int x,int y){
	return x+y*w;
}

void ppm::setSize(int w,int h){
	this->w=w;
	this->h=h;
}

void ppm::allocMem(){
	rComp=(float*)malloc(sizeof(float)*w*h);
	gComp=(float*)malloc(sizeof(float)*w*h);
	bComp=(float*)malloc(sizeof(float)*w*h);
}

void ppm::clamp(){
	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
			if(getR(x,y)<0)setR(x,y,0);
			if(getG(x,y)<0)setG(x,y,0);
			if(getB(x,y)<0)setB(x,y,0);
			if(getR(x,y)>1)setR(x,y,1);
			if(getG(x,y)>1)setG(x,y,1);
			if(getB(x,y)>1)setB(x,y,1);
		}
	}
}

void ppm::setPixel(int x,int y,float r,float g,float b){
	setR(x,y,r);
	setG(x,y,g);
	setB(x,y,b);
}

void ppm::setPixel(int x,int y,float f){
	setPixel(x,y,f,f,f);
}

void ppm::setR(int x,int y,float r){
	rComp[getInd(x,y)]=r;
}
void ppm::setG(int x,int y,float g){
	gComp[getInd(x,y)]=g;
}
void ppm::setB(int x,int y,float b){
	bComp[getInd(x,y)]=b;
}

void ppm::save(std::string fn){
	std::ofstream file;
	file.exceptions(std::ofstream::failbit|std::ofstream::badbit);
	try{
		file.open(fn.c_str());

		file<<"P3\n";
		file<<w<<" "<<h<<"\n";
		file<<PPM_PRECISION<<"\n";
		for(int y=h-1;y>=0;y--){
			for(int x=0;x<w;x++){
				int r=(int)(getR(x,y)*PPM_PRECISION);
				int g=(int)(getG(x,y)*PPM_PRECISION);
				int b=(int)(getB(x,y)*PPM_PRECISION);
				if(r<0)r=0;
				if(g<0)g=0;
				if(b<0)b=0;
				if(r>=PPM_PRECISION)r=PPM_PRECISION-1;
				if(g>=PPM_PRECISION)g=PPM_PRECISION-1;
				if(b>=PPM_PRECISION)b=PPM_PRECISION-1;
				file<<r<<" "<<g<<" "<<b<<" ";
			}
			file<<"\n";
		}
		file.close();
	}catch(std::ofstream::failure ex){
		printf("Error writing file %s\n",fn.c_str());
	}
}

void ppm::dealloc(){
	delete[] rComp;
	delete[] gComp;
	delete[] bComp;
}

float ppm::getR(int x,int y){
	return rComp[getInd(x,y)];
}
float ppm::getG(int x,int y){
	return gComp[getInd(x,y)];
}
float ppm::getB(int x,int y){
	return bComp[getInd(x,y)];
}
