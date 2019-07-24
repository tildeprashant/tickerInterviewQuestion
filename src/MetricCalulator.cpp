/*
 * MetricCalulation.cpp
 *
 *  Created on: 23-Jul-2019
 *      Author: prashant
 */

#include "MetricCalulator.h"

#include <algorithm>
#include <numeric>

/**
 *
 * @param tickerData
 */
MetricCalulator::MetricCalulator(const std::map<std::string, IpTickerInfo>& tickerData):m_refTickerData(tickerData),m_opTickerData{} {

}

/**
 *  prepare output ticker data
 */
void MetricCalulator::prepareOpTickerData() {
	OpTickerInfo temp{};

	for(auto& i: m_refTickerData){
		/* calculate Max of (Ask - Bid) */
		temp.maxOfBid = *(std::max_element( i.second.pvDiffOfAskAndBid->begin(), i.second.pvDiffOfAskAndBid->end() ));

		/* calculate Min of (Ask - Bid) */
		temp.minOfBid = *(std::min_element( i.second.pvDiffOfAskAndBid->begin(), i.second.pvDiffOfAskAndBid->end() ));

		/* calculate sum of volume */
		temp.sumOfVolume = std::accumulate( i.second.pvVolume->begin(), i.second.pvVolume->end(), 0 );

		/* calculate Max of Timestamp difference between two consecutive bids*/
		temp.maxTimeDiffBtwnTicker = *(std::max_element( i.second.pvTimeDiffBtwnTicker->begin(), i.second.pvTimeDiffBtwnTicker->end() ));

		/* calculate Sum(Bid*AskSize + Ask*BidSize)/Sum(AskSize+BidSize) */
		temp.bidRatio = std::accumulate( i.second.pvBidRatioNumerator->begin(), i.second.pvBidRatioNumerator->end(), 0.0 ) /
						std::accumulate( i.second.pvBidRatioDenominator->begin(), i.second.pvBidRatioDenominator->end(), 0.0 );

		m_opTickerData.insert({i.first, std::move(temp)});
	}
}

const std::map<std::string, OpTickerInfo>& MetricCalulator::getOpTickerData() const {
	return m_opTickerData;
}

MetricCalulator::~MetricCalulator() {
	// TODO Auto-generated destructor stub
}

