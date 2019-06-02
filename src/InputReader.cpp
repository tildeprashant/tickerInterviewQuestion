/*
 * InputReader.cpp
 *
 *  Created on: 02-Jun-2019
 *      Author: prashant
 */

#include "InputReader.h"

InputReader::InputReader():m_inputSpecefier{""} {
	// TODO Auto-generated constructor stub

}

size_t InputReader::readInputFile(const string& fileName) {
	size_t ret = 0;
	if(fileName.size()<1){
		ret = 1;
	}
	return ret;
}

string InputReader::getInputSpecifier() {

	return m_inputSpecefier;
}


size_t InputReader::readRecords() {
	return 1;
}

vector<map<string, string> > InputReader::getInputRecords()  {
	return m_inputRecords;
}

InputReader::~InputReader() {
	// TODO Auto-generated destructor stub
}

