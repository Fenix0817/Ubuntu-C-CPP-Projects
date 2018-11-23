/*
 * TextAtlas.h
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#ifndef TEXTATLAS_H_
#define TEXTATLAS_H_

#include "TextAtlasPos.h"
#include <string>

class TextAtlas {
public:
	TextAtlas();
	virtual ~TextAtlas();

	virtual TextAtlasPos getPos(char c)=0;
	virtual std::string getFile()=0;
	virtual float getAspectRatio()=0;
};

#endif /* TEXTATLAS_H_ */
