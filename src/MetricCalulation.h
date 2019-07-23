/*
 * MetricCalulation.h
 *
 *  Created on: 23-Jul-2019
 *      Author: prashant
 */

#ifndef METRICCALULATION_H_
#define METRICCALULATION_H_

#include "InputReader.h"


class MetricCalulation {
	const std::map<std::string, tickerInfo>& m_refTickerData;
	double m_maxOfBid;
	double m_minOfBid;
	int m_sumOfVolume;
	long m_timeDiffBtwnTicker;
	double m_sumOfRatio;
public:
	MetricCalulation(const std::map<std::string, tickerInfo>& tickerData);
	const double& calculateMaxOfBid();
	const double& calculateMinOfBid();
	const int& calculateSumOfVolume();
	const long& calculateTimeDiffBetweenTicker();
	const double& calculateSumRatio();
	virtual ~MetricCalulation();
};

#endif /* METRICCALULATION_H_ */
