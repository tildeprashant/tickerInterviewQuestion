#ifndef TICKER_INFO_H_
#define TICKER_INFO_H_
#include <chrono>
#include <memory>


typedef struct tickerInfo {
	std::shared_ptr< std::vector<long> > pvTimestamp;   //Timestamp
	std::shared_ptr<std::vector<double> > pvBid; //Bid
	std::shared_ptr<std::vector<int> > pvBidSize; //BidSize
	std::shared_ptr<std::vector<double> > pvAsk;  //Ask
	std::shared_ptr<std::vector<int> > pvAskSize; //AskSize
	std::shared_ptr<std::vector<int> > pvVolume;  //Volume
}tickerInfo;

#endif  // TICKER_INFO_H_
