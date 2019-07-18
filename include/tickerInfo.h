#ifndef TICKER_INFO_H_
#define TICKER_INFO_H_
#include <chrono>
#include <memory>


struct tickerInfo {
	std::shared_ptr< std::vector<long> > pvTimestamp;
	std::shared_ptr<std::vector<double> > pvBid;
	std::shared_ptr<std::vector<int> > pvBidSize;
	std::shared_ptr<std::vector<double> > pvAsk;
	std::shared_ptr<int> pvAskSize;
	std::shared_ptr<int> pvVolume;
};

#endif  // TICKER_INFO_H_
