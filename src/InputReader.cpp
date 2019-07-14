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
		}
		ret = 0;
	}
	inFile.close();

}

vector<multimap<string, string> > InputReader::getInputRecords()  {
	auto v = tokenize(this->getInputSpecifier(),R"(<|(>,<)|>)");

	for(auto& item:v) {
		cout<<item<<endl;
		multimap<string,string> m;
		m.insert(make_pair(item,""));
		m_inputRecords.push_back(move(m));
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

InputReader::~InputReader() {
	// TODO Auto-generated destructor stub
}

