/*
 * SamplerRandom.h
 *
 *  Created on: Oct 12, 2018
 *      Author: jack
 */

#ifndef SAMPLERRANDOM_H_
#define SAMPLERRANDOM_H_

#include "Sampler.h"

class SamplerRandom : public Sampler {
public:
	SamplerRandom();
	virtual ~SamplerRandom();

	SamplerRandom(int ns);

	void generateSamples();
};

#endif /* SAMPLERRANDOM_H_ */
