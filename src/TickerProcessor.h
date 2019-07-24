/*
 * TickerProcessor.h
 *
 *  Created on: 24-Jul-2019
 *      Author: prashant
 */

#ifndef TICKERPROCESSOR_H_
#define TICKERPROCESSOR_H_
#include "InputReader.h"

#include "MetricCalulator.h"

class TickerProcessor {
public:
	TickerProcessor();
	void start();
	virtual ~TickerProcessor();
};

#endif /* TICKERPROCESSOR_H_ */
