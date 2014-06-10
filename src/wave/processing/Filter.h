/*
 * Filter.h
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "wave/Samples.h"
class Filter {
public:
	Filter() {}
	virtual ~Filter(){};
	virtual void applyOn(Samples& samples) = 0;
	// TODO virtual Samples apply(Samples& samples) = 0;
};

#endif /* FILTER_H_ */