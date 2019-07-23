/*
 * MetricCalulation.cpp
 *
 *  Created on: 23-Jul-2019
 *      Author: prashant
 */

#include "MetricCalulation.h"

/**
 *
 * @param tickerData
 */
MetricCalulation::MetricCalulation(const std::map<std::string, tickerInfo>& tickerData):m_refTickerData(tickerData) {

}

/**
 * calculate Max of (Ask - Bid)
 * @return m_maxOfBid
 */
const double& MetricCalulation::calculateMaxOfBid() {
	return m_maxOfBid;
}

/**
 * calculate Min of (Ask - Bid)
 * @return m_minOfBid
 */
const double& MetricCalulation::calculateMinOfBid() {
	return m_minOfBid;
}

/**
 * calculate sum of volume
 * @return m_sumOfVolume
 */
const int& MetricCalulation::calculateSumOfVolume() {
	return m_sumOfVolume;
}

/**
 * calculate Max of Timestamp difference between two consecutive bids
 *  @return m_timeDiffBtwnTicker
 */
const long& MetricCalulation::calculateTimeDiffBetweenTicker() {
	return m_timeDiffBtwnTicker;
}

/**
 * calculate Sum(Bid*AskSize + Ask*BidSize)/Sum(AskSize+BidSize)
 *
 * @return m_sumOfRatio
 */
const double& MetricCalulation::calculateSumRatio() {
	return m_sumOfRatio;
}

MetricCalulation::~MetricCalulation() {
	// TODO Auto-generated destructor stub
}

