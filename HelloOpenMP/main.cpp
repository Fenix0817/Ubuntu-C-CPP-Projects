/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include <math.h>
#include "ppm.h"
#include <chrono>
#include "complex.h"
#include "omp.h"
using namespace std::chrono;

///https://stackoverflow.com/a/19555298/9609025
long curTime(){
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
	);
	return ms.count();
}
int main(){
#pragma omp parallel for
	for(int i=0;i<10;i++){
		printf("%i\n",i);
	}
	int w=1000;
	int h=1000;
	ppm img;
	img.setSize(w,h);
	img.allocMem();

	long start,end;

	start=curTime();
#pragma omp parallel for
	for(int x=0;x<w;x++){
#pragma omp parallel for
		for(int y=0;y<h;y++){
//			printf("%i %i\n",x,y);
			float fx=x;
			float fy=y;
			fx/=w;
			fy/=h;
			fx*=4;
			fy*=4;
			fx-=2;
			fy-=2;

			complex c=fromXY(fx,fy);
			complex c0=c;

			int max=50;
			int i=0;
			for(i=0;i<max&&c.r<10000;i++){
				c=c^2;
				c=c+c0;
			}
			float f=((float)i)/((float)max);
			img.setPixel(x,y,f);
		}
	}
	end=curTime();

	unsigned long diff1=end-start;

	start=curTime();
	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
//			printf("%i %i\n",x,y);
			float fx=x;
			float fy=y;
			fx/=w;
			fy/=h;
			fx*=4;
			fy*=4;
			fx-=2;
			fy-=2;

			complex c=fromXY(fx,fy);
			complex c0=c;

			int max=50;
			int i=0;
			for(i=0;i<max&&c.r<10000;i++){
				c=c^2;
				c=c+c0;
			}
			float f=((float)i)/((float)max);
			img.setPixel(x,y,f);
		}
	}
	end=curTime();

	long diff2=end-start;

	printf("With OMP    : %lums\n",diff1);
	printf("Without OMP : %lums\n",diff2);
	printf("Speedup     : %lums\n",diff2-diff1);

	img.clamp();
	img.save("mandelbrot.ppm");
	img.dealloc();

	return 0;
}
