/*
 * Filter.h
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "../Samples.h"
class Filter {
public:
	virtual ~Filter(){};
	virtual void applyOn(Samples& samples) {};
	// TODO virtual Samples applyOn(Samples& samples) = 0;
};

#endif /* FILTER_H_ */
