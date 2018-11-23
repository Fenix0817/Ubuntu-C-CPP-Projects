/*
 * TextAtlasMonospaced.h
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#ifndef TEXTATLASMONOSPACED_H_
#define TEXTATLASMONOSPACED_H_

#include "TextAtlas.h"

class TextAtlasMonospaced : public TextAtlas {
public:
	TextAtlasMonospaced();
	virtual ~TextAtlasMonospaced();

	TextAtlasPos getPos(char c);
	std::string getFile();
	float getAspectRatio();

};

#endif /* TEXTATLASMONOSPACED_H_ */
