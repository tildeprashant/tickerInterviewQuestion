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

class InputReader {
	std::string m_inputSpecefier;
	std::string m_outputSpecefier;
	std::string m_outputString;
	std::map<std::string,int> m_inputRecords;
	std::map<std::string,int> m_outputRecords;
	std::map<std::string,IpTickerInfo> m_tickerInfo;
private:
	void calculateOutputMetrics();
public:
	InputReader();
	size_t readIoSpecifiers(const std::string& fileName);
	size_t readRecords(const std::string& fileName);
	std::map<std::string,int> readInputSpecifier(const std::string& line);
	std::vector<std::string> tokenize(const std::string& input, const std::string delim="\\s+");
	void fillTickerInfo(auto& inputVector);
	const std::map<std::string,IpTickerInfo>& getTickerInfo()const;
	const std::string& getOutputString();
	virtual ~InputReader();
};

#endif /* INPUTREADER_H_ */
