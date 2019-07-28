#ifndef TICKER_INFO_H_
#define TICKER_INFO_H_
#include <vector>
#include <memory>


typedef struct IpTickerInfo {

	std::shared_ptr<std::vector<double> > pvDiffOfAskAndBid; //Ask - Bid
	std::shared_ptr<std::vector<int> > pvVolume;  //Volume
	std::shared_ptr< std::vector<long> > pvTimeDiffBtwnTicker;   //Timestamp difference between two consecutive bids
	std::shared_ptr<std::vector<double> > pvBidRatioNumerator;  //Bid*AskSize + Ask*BidSize
	std::shared_ptr<std::vector<int> > pvBidRatioDenominator;  //AskSize+BidSize
	std::shared_ptr<long> pLastTimestamp;  // last value of timestamp
}IpTickerInfo;

typedef struct OpTickerInfo {
	std::string ticker;        //ticker
	double maxOfBid;      	   //max of (Ask - Bid)
	double minOfBid;      	   //min of (Ask - Bid)
	int    sumOfVolume;   	   //sum of volume
	long   maxTimeDiffBtwnTicker; //max of Timestamp difference between two consecutive bids
	double bidRatio;       	   //Sum(Bid*AskSize + Ask*BidSize)/Sum(AskSize+BidSize)
}OpTickerInfo;
#endif  // TICKER_INFO_H_
