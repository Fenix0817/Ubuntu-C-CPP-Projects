/*
 * ppm.h
 *
 *  Created on: Sep 13, 2018
 *      Author: jack
 */

#ifndef PPM_H_
#define PPM_H_

#include <iostream>
#include <fstream>

#define PPM_PRECISION 1000

class ppm {
public:
	ppm();
	virtual ~ppm();

	float*rComp;
	float*gComp;
	float*bComp;

	int w;
	int h;

	int getInd(int x,int y);

	void setSize(int w,int h);

	void allocMem();

	void clamp();

	void setPixel(int x,int y,float r,float g,float b);

	void setR(int x,int y,float r);
	void setG(int x,int y,float g);
	void setB(int x,int y,float b);

	void save(std::string fn);

	void dealloc();

	float getR(int x,int y);
	float getG(int x,int y);
	float getB(int x,int y);
};

#endif /* PPM_H_ */
