#ifndef TICKER_INFO_H_
#define TICKER_INFO_H_
#include <chrono>

struct tickerInfo {
	std::chrono::time_point<std::chrono::system_clock> timestamp;
	double bid;
	int bidSize;
	double ask;
	int askSize;
	int volume;
};

#endif  // TICKER_INFO_H_
