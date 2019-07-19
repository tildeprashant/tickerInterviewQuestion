/*
 * InputReader.h
 *
 *  Created on: 02-Jun-2019
 *      Author: prashant
 */

#ifndef INPUTREADER_H_
#define INPUTREADER_H_
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <tickerInfo.h>
using namespace std;

class InputReader {
	string m_inputSpecefier;
	std::map<string,int> m_inputRecords;
	multimap<std::string,tickerInfo> m_tickerInfo;
	string m_fileIpFormat;
	string m_fileIpRecord;
public:
	InputReader();
	size_t readInputFile();
	string getInputSpecifier() ;
	size_t readRecords();
	std::map<string,int> getInputRecords();
	vector<string> tokenize(const string& input, string delim="\\s+");
	void setFileName(string format, string recordFile);
	const string& getFileNameIpFormat() const;
	const string& getFileNameIpRecord() const;
	void fillTickerInfo(auto& inputVector);
	virtual ~InputReader();
};

#endif /* INPUTREADER_H_ */
