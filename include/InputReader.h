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

class InputReader {
	string m_inputSpecefier;
	vector< map<string, string > > m_inputRecords;
public:
	InputReader();
	size_t readInputFile(const string& fileName);
	string getInputSpecifier() ;
	size_t readRecords();
	vector< map<string, string > > getInputRecords();

	virtual ~InputReader();
};

#endif /* INPUTREADER_H_ */
