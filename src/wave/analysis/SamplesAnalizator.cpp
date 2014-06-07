/*
 * WaveFileAnalizator.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#include "SamplesAnalizator.h"

SamplesAnalizator::SamplesAnalizator() {

}

SamplesAnalizator::~SamplesAnalizator() {
}

double SamplesAnalizator::findAmplitude(Samples& samples) {
	double result = 0;
	for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
		double sample = samples.getSample(i);
		if (fabs(sample) > result) {
			result = fabs(sample);
		}
	}
	return result;
}

int SamplesAnalizator::countZeroCrossings(Samples& samples) {
	int result = 0;
	for (unsigned int i = 0; i < samples.getNumberOfSamples() - 1; ++i) {
		double sample = samples.getSample(i);
		double nextSample = samples.getSample(i + 1);
		if (sample * nextSample <= 0) {
			++result;
		}
	}
	return result;
}

// FIXME Issue #22 write test for this function and uncomment
//double WaveFileAnalizator::findPeriod(NormalizedSamplesList& samples) {
//
//	int result = 0;
//	unsigned int i = 0;
//	bool startCalt = true;
//	unsigned int start = 0;
//	for (i = 0; i < samples.getNumberOfSamples() - 1; ++i) {
//		double sample = samples.getSample(i);
//		double nextSample = samples.getSample(i + 1);
//
//		if (sample * nextSample <= 0) {
//			++result;
//			if (startCalt) {
//				startCalt = false;
//				start = i;
//			}
//		}
//		if (result == 3) {
//			break;
//		}
//	}
//	result = (i - start);
//	// because of no tests I'm not able to examine if it works properly
//	// Before refactoring it was: result = (i - start) / waveFile.getByteRate();
//
//	return result;
//}


double SamplesAnalizator::percentageAbove(Samples& samples,
		double percentOfMax) {
	int aboveCounter = 0;
	int allCounter = 0;

	for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
		++allCounter;
		double sample = samples.getSample(i);
		if (fabs(sample) > percentOfMax) {
			++aboveCounter;
		}
	}

	return aboveCounter * 1.0 / allCounter;
}

double SamplesAnalizator::percetnageBelow(Samples& samples,
		double percentOfMax) {
	return 1.0 - percentageAbove(samples, percentOfMax);
}



WaveProperties SamplesAnalizator::getAllProperties(Samples& samples) {
	WaveProperties result;
	result.amplitude = findAmplitude(samples);
	result.zeroCrossings = countZeroCrossings(samples);
	result.lenghtInSeconds = samples.getLenghtInSeconds();
	return result;
}
