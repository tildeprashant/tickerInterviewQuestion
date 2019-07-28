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
	std::map<std::string,int>& m_refOpRecords;
	std::vector<OpTickerInfo> m_opTickerData;
	std::vector<std::vector<std::string>> m_vvTickerMap;
public:
	MetricCalulator(const std::map<std::string, IpTickerInfo>& tickerData, std::map<std::string,int>& records);
	void prepareOpTickerData();
	virtual ~MetricCalulator();
	const std::map<std::string, OpTickerInfo>& getOpTickerData() const;
	const std::vector<std::vector<std::string>>& getOpTickerMap() const;
	void setOpTickerMap(const OpTickerInfo& info);
};

#endif /* METRICCALULATOR_H_ */
