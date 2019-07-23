#ifndef TICKER_INFO_H_
#define TICKER_INFO_H_
#include <chrono>
#include <memory>


typedef struct tickerInfo {

	std::shared_ptr<std::vector<double> > pvDiffOfAskAndBid; //Ask - Bid
	std::shared_ptr<std::vector<int> > pvVolume;  //Volume
	std::shared_ptr< std::vector<long> > pvTimeDiffBtwnTicker;   //Timestamp difference between two consecutive bids
	std::shared_ptr<std::vector<double> > pvBidRatioNumerator;  //Bid*AskSize + Ask*BidSize
	std::shared_ptr<std::vector<int> > pvBidRatioDenominator;  //AskSize+BidSize
	long lastTimestamp;  // last value of timestamp
}tickerInfo;

#endif  // TICKER_INFO_H_
