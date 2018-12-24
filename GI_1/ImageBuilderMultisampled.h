/*
 * ImageBuilderMultisampled.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef IMAGEBUILDERMULTISAMPLED_H_
#define IMAGEBUILDERMULTISAMPLED_H_

#include "ImageBuilder.h"

class ImageBuilderMultisampled : public ImageBuilder {
public:
	ImageBuilderMultisampled();
	virtual ~ImageBuilderMultisampled();

	inline ImageBuilderMultisampled(int w,int h,int ns,Tracer*t){
		this->w=w;
		this->h=h;
		this->ns=ns;
		this->tracer=t;
	}

	int ns;

	void buildImage();
};

#endif /* IMAGEBUILDERMULTISAMPLED_H_ */
