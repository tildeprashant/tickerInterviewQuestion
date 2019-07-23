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

size_t InputReader::readInputFile() {
	size_t ret = 0;
	auto fileName = getFileNameIpFormat();
	if(fileName.size()<1){
		ret = 1;
	}

	std::ifstream inFile;
	try{
		inFile.open(fileName.c_str());
	}
	catch(std::exception& e){
		std::cout<<e.what()<<"\n";
		inFile.close();
	}

	if (inFile.is_open()){
		getline(inFile,m_inputSpecefier);
		std::cout<<m_inputSpecefier<<"\n";
		this->getInputRecords();
		ret = 0;
	}
	inFile.close();
	return ret;
}

std::string InputReader::getInputSpecifier() {

	return m_inputSpecefier;
}


size_t InputReader::readRecords() {
	size_t ret = 0;
	std::string line = "";
	auto fileName = getFileNameIpRecord();
	if(fileName.size()<1){
		ret = 1;
	}

	std::ifstream inFile;
	try{
		inFile.open(fileName.c_str());
	}
	catch(std::exception& e){
		std::cout<<e.what()<<"\n";
		inFile.close();
	}

	if (inFile.is_open()){
		while(getline(inFile,line)) {
			std::cout<<line<<"\n";
			auto v = tokenize(line,R"(,|\r)");
			if(v.size()!= m_inputRecords.size()){
				std::cout<<"metric information does not have enough data! dropping the record.\n";
			}else {
				this->fillTickerInfo(v);
			}
			/* empty the vector for next records to be filled. */
			v.clear();
		}
		ret = 0;
	}
	inFile.close();
	return ret;
}

std::map<std::string,int> InputReader::getInputRecords()  {


	/* trim beginnning and trailing angle brackets(<,>) from specifier string */
	auto specifierString = std::regex_replace(m_inputSpecefier, std::regex(R"(^\s*<|^<|>\s$|>$)"), std::string(""));

	auto v = tokenize(specifierString,R"(>,<)");
	int i = 0;

	/* prepare metric index map */
	for(auto& item:v){
		m_inputRecords.insert(std::make_pair(item,i++));
	}

	return m_inputRecords;
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

void InputReader::setFileName(std::string format, std::string recordFile) {
	m_fileIpFormat = format;
	m_fileIpRecord = recordFile;
}

const std::string& InputReader::getFileNameIpFormat() const {
	return m_fileIpFormat;
}

const std::string& InputReader::getFileNameIpRecord() const {
	return m_fileIpRecord;
}

void InputReader::fillTickerInfo(auto& indexMap) {
	tickerInfo info;

	auto key = indexMap[m_inputRecords["Ticker"]];

	auto tempDiffOfAskAndBid = stof(indexMap[m_inputRecords.at("Ask")]) - stof(indexMap[m_inputRecords.at("Bid")]);

	auto tempVolume = stoi(indexMap[m_inputRecords.at("Volume")]);

	auto tempBidRatioNumerator = stof(indexMap[m_inputRecords.at("Bid")]) * stoi(indexMap[m_inputRecords.at("AskSize")]) +
					             stof(indexMap[m_inputRecords.at("Ask")]) * stoi(indexMap[m_inputRecords.at("BidSize")]);

	auto tempBidRatioDenominator = stof(indexMap[m_inputRecords.at("AskSize")]) + stoi(indexMap[m_inputRecords.at("BidSize")]);



	auto it = m_tickerInfo.find(key);
	/* if ticker any ticker is already present in the map augument its information else create it. */
	if(it != m_tickerInfo.end()){
		/*extract the index of the metrics from input metrics format map and use index to fill the metrics info */
		it->second.pvDiffOfAskAndBid->push_back(tempDiffOfAskAndBid);
		it->second.pvVolume->push_back(tempVolume);

		it->second.pvTimeDiffBtwnTicker->push_back(stol(indexMap[m_inputRecords.at("Timestamp")]) - it->second.lastTimestamp);
		it->second.lastTimestamp = stol(indexMap[m_inputRecords.at("Timestamp")]);

		it->second.pvBidRatioNumerator->push_back(stof(indexMap[m_inputRecords.at("Ask")]));
		it->second.pvBidRatioDenominator->push_back(stoi(indexMap[m_inputRecords.at("AskSize")]));
	}
	else{
		/*extract the index of the metrics from input metrics format map and use index to fill the metrics info */

		info.pvDiffOfAskAndBid = std::make_shared<std::vector<double> >(1,tempDiffOfAskAndBid);

		info.pvVolume = std::make_shared<std::vector<int> >( 1,tempVolume);

		info.pvTimeDiffBtwnTicker = std::make_shared<std::vector<long> >( 1,stol(indexMap[m_inputRecords.at("Timestamp")]));

		info.pvBidRatioNumerator = std::make_shared<std::vector<double> >( 1,tempBidRatioNumerator);

		info.pvBidRatioDenominator = std::make_shared<std::vector<int> >( 1,tempBidRatioDenominator);
		info.lastTimestamp = stol(indexMap[m_inputRecords.at("Timestamp")]);

		m_tickerInfo.insert(make_pair(key,info));
	}
}

const std::map<std::string, tickerInfo>& InputReader::getTickerInfo() const {
	return m_tickerInfo;
}

InputReader::~InputReader() {
	// TODO Auto-generated destructor stub
}

