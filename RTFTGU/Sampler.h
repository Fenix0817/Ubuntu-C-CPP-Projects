/*
 * Sampler.h
 *
 *  Created on: Oct 12, 2018
 *      Author: jack
 */

#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "utils.h"

class Sampler {
public:
	Sampler();
	virtual ~Sampler();

	Sampler(int ns);

	void shuffleX();
	void shuffleY();

	virtual void generateSamples()=0;

	void mapSamplesToSphere();
	void mapSamplesToHemisphere();

	Vector3 sampleSphere();
	Vector3 sampleHemisphere();

	int jump=30;
	int indexSphere=0;
	int indexHemisphere=0;

	int numSamples;

	std::vector<Vector2> samples;
	std::vector<Vector3> samplesSphere;
	std::vector<Vector3> samplesHemisphere;
};

#endif /* SAMPLER_H_ */
