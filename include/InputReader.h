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
using namespace std;

struct tickerInfo {
	int timestamp;
	double bid;
	int bidSize;
	double ask;
	int askSize;
	int volume;
};

class InputReader {
	string m_inputSpecefier;
	vector< multimap<string, string > > m_inputRecords;
	multimap<int,tickerInfo> m_tickerInfo;
	string m_fileIpFormat;
	string m_fileIpRecord;
public:
	InputReader();
	size_t readInputFile();
	string getInputSpecifier() ;
	size_t readRecords();
	vector< multimap<string, string > > getInputRecords();
	vector<string> tokenize(const string& input, string delim="\\s+");
	void setFileName(string format, string recordFile);
	const string& getFileNameIpFormat() const;
	const string& getFileNameIpRecord() const;
	virtual ~InputReader();
};

#endif /* INPUTREADER_H_ */
