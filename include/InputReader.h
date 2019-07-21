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
	std::map<std::string,int> m_inputRecords;
	std::map<std::string,tickerInfo> m_tickerInfo;
	std::string m_fileIpFormat;
	std::string m_fileIpRecord;
public:
	InputReader();
	size_t readInputFile();
	std::string getInputSpecifier() ;
	size_t readRecords();
	std::map<std::string,int> getInputRecords();
	std::vector<std::string> tokenize(const std::string& input, const std::string delim="\\s+");
	void setFileName(std::string format, std::string recordFile);
	const std::string& getFileNameIpFormat() const;
	const std::string& getFileNameIpRecord() const;
	void fillTickerInfo(auto& inputVector);
	const std::map<std::string,tickerInfo>& getTickerInfo()const;
	virtual ~InputReader();
};

#endif /* INPUTREADER_H_ */
