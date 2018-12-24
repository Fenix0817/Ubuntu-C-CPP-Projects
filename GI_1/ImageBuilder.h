/*
 * ImageBuilder.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef IMAGEBUILDER_H_
#define IMAGEBUILDER_H_

#include <ppm.h>
#include "Tracer.h"

class ImageBuilder {
public:
	ImageBuilder();
	virtual ~ImageBuilder();

	inline ImageBuilder(int w,int h,Tracer*t){
		this->w=w;
		this->h=h;
		this->tracer=t;
	}

	int w;
	int h;

	Tracer*tracer;

	ppm img;

	inline void init(){
		img.setSize(w,h);
		img.allocMem();
	}

	virtual void buildImage()=0;

	inline void save(std::string fn){
		img.save(fn);
	}

	inline void end(){
		img.dealloc();
	}
};

#endif /* IMAGEBUILDER_H_ */
