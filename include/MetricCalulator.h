/*
 * MetricCalulator.h
 *
 *  Created on: 23-Jul-2019
 *      Author: prashant
 */

#ifndef METRICCALULATOR_H_
#define METRICCALULATOR_H_

#include "tickerInfo.h"
#include "InputReader.h"


class MetricCalulator {
	const std::map<std::string, IpTickerInfo>& m_refTickerData;
	std::map<std::string, OpTickerInfo> m_opTickerData;
public:
	MetricCalulator(const std::map<std::string, IpTickerInfo>& tickerData);
	void prepareOpTickerData();
	virtual ~MetricCalulator();
	const std::map<std::string, OpTickerInfo>& getOpTickerData() const;
};

#endif /* METRICCALULATOR_H_ */
