/*
 * MetricCalulation.cpp
 *
 *  Created on: 23-Jul-2019
 *      Author: prashant
 */

#include <MetricCalulator.h>
#include <algorithm>
#include <numeric>
#include <iostream>

/**
 *
 * @param tickerData
 */
MetricCalulator::MetricCalulator(const std::map<std::string, IpTickerInfo>& tickerData, std::map<std::string,int>& records)
								:m_refTickerData{tickerData},m_refOpRecords{records} {

}

/**
 *  prepare output ticker data
 */
void MetricCalulator::prepareOpTickerData() {
	OpTickerInfo temp{};

	for(auto& i: m_refTickerData){
		/* ticker */
		temp.ticker = i.first;

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

		//m_opTickerData.push_back(std::move(temp));
		this->setOpTickerMap(temp);
	}
}

/*const std::vector<OpTickerInfo>& MetricCalulator::getOpTickerData() const {
	return m_opTickerData;
}*/

MetricCalulator::~MetricCalulator() {
	// TODO Auto-generated destructor stub
}

const std::map<std::string, std::vector<std::string>>& MetricCalulator::getOpTickerMap() const {
	return m_opTickerMap;
}

void MetricCalulator::setOpTickerMap(const OpTickerInfo& info) {

	auto key = info.ticker;
	std::vector<std::string> v(m_refOpRecords.size() -1); //-1 because "Ticker" will be saved as key.


	v[m_refOpRecords.at("maxOfBid")-1] = std::to_string(info.maxOfBid).substr(0, std::to_string(info.maxOfBid).find(".") + 4);
	v[m_refOpRecords.at("minOfBid")-1] = std::to_string(info.minOfBid).substr(0, std::to_string(info.minOfBid).find(".") + 4);
	v[m_refOpRecords.at("sumOfVolume")-1] = std::to_string(info.sumOfVolume);
	v[m_refOpRecords.at("maxTimeDiffBtwnTicker")-1] = std::to_string(info.maxTimeDiffBtwnTicker);
	v[m_refOpRecords.at("bidRatio")-1] = std::to_string(info.bidRatio).substr(0, std::to_string(info.bidRatio).find(".") + 4);
	m_opTickerMap.insert({std::move(key), std::move(v)});
}
