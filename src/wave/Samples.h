/*
 * SampleList.h
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#ifndef SAMPLELIST_H_
#define SAMPLELIST_H_
#include <stdint.h>
#include <complex>

#include "WaveFile.h"
#include "WaveUtils.h"

typedef std::complex<double> cx;


class FastFourierTransformFilter;
class Samples {
public:
	friend class FastFourierTransformFilter;
public:
	Samples(WaveFile & waveFile);
	Samples(WaveFile && waveFile);
	virtual ~Samples();
	virtual cx& operator[](unsigned int i) const;
	virtual double getSample(unsigned int i) const;
	virtual cx& getSampleCx(unsigned int i) const;
	virtual void setSample(uint32_t index, double value);
	virtual uint32_t getNumberOfSamples() const;
	virtual double getLenghtInSeconds() const;
	void setSampleListData(uint32_t numberOfSamples, cx * data);
	Samples();
protected:
	cx * samples = nullptr;
	uint32_t numberOfSamples;
	double lenghtInSeconds;
	uint32_t sampleRate;
};

#endif /* SAMPLELIST_H_ */
