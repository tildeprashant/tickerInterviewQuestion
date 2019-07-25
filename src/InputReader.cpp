/*
 * InputReader.cpp
 *
 *  Created on: 02-Jun-2019
 *      Author: prashant
 */

#include "InputReader.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <utility>

InputReader::InputReader():m_inputSpecefier{""} {
	// TODO Auto-generated constructor stub

}

size_t InputReader::readIoSpecifiers(const std::string& fileName) {
	size_t ret = 1;

	if(fileName.size()<1){
		std::cerr<<"readIoSpecifiers: file name is empty"<<"\n";
		return ret;
	}

	std::ifstream inFile;
	inFile.open(fileName.c_str());

	if(!inFile.is_open()) {
		std::cerr<<"unable to open input file: "<<fileName.c_str()<<"\n";
	}
	else {
		std::string line{};

		getline(inFile,line);
		m_inputRecords = this->readInputSpecifier(line);

		m_outputRecords = this->readInputSpecifier(line);
		for(auto& i:m_outputRecords){
			std::cout<<i.first<<" : "<<i.second<<"\n";
		}
		ret = 0;
		inFile.close();
	}



	return ret;
}

size_t InputReader::readRecords(const std::string& fileName) {
	size_t ret = 1;
	std::string line = "";

	if(fileName.size()<1){
		std::cerr<<"readRecords: file name is empty"<<"\n";
		return ret;
	}

	std::ifstream inFile;
	inFile.open(fileName.c_str());
	if(!inFile.is_open()){
		std::cerr<<"unable to open input file: "<<fileName.c_str()<<"\n";
	}
	else {
		while(getline(inFile,line)) {
			auto v = tokenize(line,R"(,|\r)");
			if(v.size()!= m_inputRecords.size()){
				std::cout<<"metric information does not have enough data! dropping the record.\n";
			}else {
				this->fillTickerInfo(v);
			}
			/* empty the vector for next records to be filled. */
			v.clear();
		}
	}
	ret = 0;
	inFile.close();
	return ret;
}

std::map<std::string,int> InputReader::readInputSpecifier(const std::string& line)  {

	std::map<std::string,int> tempMap{};
	/* trim beginning and trailing angle brackets(<,>) from specifier string */
	auto specifierString = std::regex_replace(line, std::regex(R"(^\s*<|^<|>\s$|>$)"), std::string(""));

	auto v = tokenize(specifierString,R"(>,<)");
	int i = 0;

	/* prepare metric index map */
	for(auto& item:v){
		tempMap.insert(std::make_pair(item,i++));
	}

	return std::move(tempMap);
}

std::vector<std::string> InputReader::tokenize(const std::string& input, const std::string delim) {

	//create regex object from delimiter
	std::regex regStr(delim);

    /* trim whitespace character from input string */
    auto inStr = std::regex_replace(input, std::regex("\\s+"), std::string(""));

    /* tokenize string and copy it to a vector */
    std::sregex_token_iterator it(inStr.begin(), inStr.end(), regStr, -1),end;
    std::vector<std::string> v;
    copy(it,end,back_inserter(v));

    return move(v);
}

void InputReader::fillTickerInfo(auto& indexMap) {
	IpTickerInfo info{};

	auto key = indexMap[m_inputRecords["Ticker"]];

	auto tempDiffOfAskAndBid = stof(indexMap[m_inputRecords.at("Ask")]) - stof(indexMap[m_inputRecords.at("Bid")]);

	auto tempVolume = stoi(indexMap[m_inputRecords.at("Volume")]);

	auto tempBidRatioNumerator = stof(indexMap[m_inputRecords.at("Bid")]) * stoi(indexMap[m_inputRecords.at("AskSize")]) +
					             stof(indexMap[m_inputRecords.at("Ask")]) * stoi(indexMap[m_inputRecords.at("BidSize")]);

	auto tempBidRatioDenominator = stoi(indexMap[m_inputRecords.at("AskSize")]) + stoi(indexMap[m_inputRecords.at("BidSize")]);

	auto it = m_tickerInfo.find(key);

	/* if ticker any ticker is already present in the map augument its information else create it. */
	if(it != m_tickerInfo.end()){
		/*extract the index of the metrics from input metrics format map and use index to fill the metrics info */
		it->second.pvDiffOfAskAndBid->push_back(tempDiffOfAskAndBid);
		it->second.pvVolume->push_back(tempVolume);

		it->second.pvTimeDiffBtwnTicker->push_back(stol(indexMap[m_inputRecords.at("Timestamp")]) - *(it->second.pLastTimestamp) );
		*(it->second.pLastTimestamp) = stol(indexMap[m_inputRecords.at("Timestamp")]);

		it->second.pvBidRatioNumerator->push_back(tempBidRatioNumerator);
		it->second.pvBidRatioDenominator->push_back(tempBidRatioDenominator);
	}
	else{
		/*extract the index of the metrics from input metrics format map and use index to fill the metrics info */

		info.pvDiffOfAskAndBid 	  = std::make_shared<std::vector<double>>( std::vector<double>{tempDiffOfAskAndBid});
		info.pvVolume 		  	  = std::make_shared<std::vector<int>>   ( std::vector<int>{tempVolume} );
		info.pvTimeDiffBtwnTicker = std::make_shared<std::vector<long>>  ( std::vector<long> {stol(indexMap[m_inputRecords.at("Timestamp")])} );
		info.pvBidRatioNumerator  = std::make_shared<std::vector<double>>( std::vector<double>{tempBidRatioNumerator} );
		info.pvBidRatioDenominator= std::make_shared<std::vector<int>>	 ( std::vector<int>{tempBidRatioDenominator} );
		info.pLastTimestamp 	  = std::make_shared<long>		         ( long{stol(indexMap[m_inputRecords.at("Timestamp")])});

		m_tickerInfo.insert({key, std::move(info)});
	}
}

const std::map<std::string, IpTickerInfo>& InputReader::getTickerInfo() const {
	return m_tickerInfo;
}

InputReader::~InputReader() {
	// TODO Auto-generated destructor stub
}

