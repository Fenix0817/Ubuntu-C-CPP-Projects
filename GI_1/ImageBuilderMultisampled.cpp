/*
 * ImageBuilderMultisampled.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#include "ImageBuilderMultisampled.h"

ImageBuilderMultisampled::ImageBuilderMultisampled() {
	// TODO Auto-generated constructor stub

}

ImageBuilderMultisampled::~ImageBuilderMultisampled() {
	// TODO Auto-generated destructor stub
}

void ImageBuilderMultisampled::buildImage(){
#pragma omp parallel for
	for(int x=0;x<w;x++){
#pragma omp parallel for
		for(int y=0;y<h;y++){
			vec3 total(0,0,0);
#pragma omp parallel for
			for(int i=0;i<ns;i++){
				total+=tracer->getColor(x,y);
			}
			if(ns!=0){
				total/=ns;
//				printf("%i %i\n",x,y);
			}
			img.setPixel(x,y,total.x,total.y,total.z);
		}
	}
}
