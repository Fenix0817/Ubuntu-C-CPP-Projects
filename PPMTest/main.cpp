/*
 * main.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: jack
 */


#include "ppm.h"

int main(){

	ppm img;
	img.setSize(500,500);
	img.allocMem();

	for(int x=0;x<img.w;x++){
		for(int y=0;y<img.h;y++){
			float fx=1.0*x/img.w*4.0-2.0;
			float fy=1.0*y/img.h*4.0-2.0;

			float x0=fx;
			float y0=fy;

			float i=0;
			float max=30;
			while(fx*fx+fy*fy<4.0&&i<max){
				float nx=fx*fx-fy*fy+x0;
				float ny=2*fx*fy+y0;
				fx=nx;
				fy=ny;
				i++;
			}

			float f=i/max;

			img.setPixel(x,y,  f,f,f);

		}
	}

	img.clamp();
	img.save("mandelbrot.ppm");
	img.dealloc();

	return 0;
}
