/*
 * SamplerRandom.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: jack
 */

#include "SamplerRandom.h"

SamplerRandom::SamplerRandom() {
	// TODO Auto-generated constructor stub

}

SamplerRandom::~SamplerRandom() {
	// TODO Auto-generated destructor stub
}


SamplerRandom::SamplerRandom(int ns){
	numSamples=ns;
}

void SamplerRandom::generateSamples(){
	for(int i=0;i<numSamples;i++){
		samples.push_back(Vector2(randomFloat(),randomFloat()));
	}
}
