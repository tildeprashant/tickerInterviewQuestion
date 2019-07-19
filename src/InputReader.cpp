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

	ifstream inFile;
	try{
		inFile.open(fileName.c_str());
	}
	catch(exception& e){
		cout<<e.what()<<endl;
	}

	if (inFile.is_open()){
		getline(inFile,m_inputSpecefier);
		cout<<m_inputSpecefier<<endl;
		ret = 0;
	}
	return ret;
}

string InputReader::getInputSpecifier() {

	return m_inputSpecefier;
}


size_t InputReader::readRecords() {
	size_t ret = 0;
	string line = "";
	auto fileName = getFileNameIpRecord();
	if(fileName.size()<1){
		ret = 1;
	}

	ifstream inFile;
	try{
		inFile.open(fileName.c_str());
	}
	catch(exception& e){
		cout<<e.what()<<endl;
		inFile.close();
	}

	if (inFile.is_open()){
		while(getline(inFile,line)) {
			cout<<line<<endl;
			auto v = tokenize(line,R"(,|\r)");
			this->fillTickerInfo(v);
		}
		ret = 0;
	}
	inFile.close();
}

map<string,int> InputReader::getInputRecords()  {

	auto v = tokenize(this->getInputSpecifier(),R"(<|(>,<)|>)");
	int i = 0;

	/* prepare metric index map */
	for(auto& item:v){
		m_inputRecords.insert(std::make_pair(item,i++));
	}

	return m_inputRecords;
}

vector<string> InputReader::tokenize(const string& input, string delim) {
    regex regStr(delim);
    sregex_token_iterator it(input.begin(), input.end(), regStr, -1),end;
    //sregex_token_iterator end;
    vector<string> v;
    copy(it,end,back_inserter(v));
    return move(v);
}

void InputReader::setFileName(string format, string recordFile) {
	m_fileIpFormat = format;
	m_fileIpRecord = recordFile;
}

const string& InputReader::getFileNameIpFormat() const {
	return m_fileIpFormat;
}

const string& InputReader::getFileNameIpRecord() const {
	return m_fileIpRecord;
}

void InputReader::fillTickerInfo(auto& indexMap) {
	tickerInfo info;


	auto key = indexMap[m_inputRecords["Ticker"]];
	auto it = m_tickerInfo.find(key);
	if(it != m_tickerInfo.end()){
		it->second.pvTimestamp->push_back(stoi(indexMap[m_inputRecords["Timestamp"]]));
		it->second.pvBid->push_back(stof(indexMap[m_inputRecords["Bid"]]));
		it->second.pvBidSize->push_back(stoi(indexMap[m_inputRecords["BidSize"]]));
		it->second.pvAsk->push_back(stof(indexMap[m_inputRecords["Ask"]]));
		it->second.pvAskSize->push_back(stoi(indexMap[m_inputRecords["AskSize"]]));
		it->second.pvVolume->push_back(stoi(indexMap[m_inputRecords["Volume"]]));
	}
	else{
		info.pvTimestamp = std::make_shared<std::vector<long> >(1,stoi(indexMap[m_inputRecords["Timestamp"]]));
		info.pvBid = std::make_shared<std::vector<double> >(1,stof(indexMap[m_inputRecords["Bid"]]));
		info.pvBidSize = std::make_shared<std::vector<int> >(1,stoi(indexMap[m_inputRecords["BidSize"]]));
		info.pvAsk = std::make_shared<std::vector<double> >(1,stof(indexMap[m_inputRecords["Ask"]]));
		info.pvAskSize = std::make_shared<std::vector<int> >(1,stoi(indexMap[m_inputRecords["AskSize"]]));
		info.pvVolume = std::make_shared<std::vector<int> >( 1,stoi(indexMap[m_inputRecords["Volume"]]));
		m_tickerInfo.insert(make_pair(key,info));
	}
}

InputReader::~InputReader() {
	// TODO Auto-generated destructor stub
}

