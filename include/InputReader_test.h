/*
 * InputReader_test.h
 *
 *  Created on: 20-Jul-2019
 *      Author: prashant
 */

#ifndef INPUTREADER_TEST_H_
#define INPUTREADER_TEST_H_

#include <limits.h>
#include "InputReader.h"
#include "gtest/gtest.h"

namespace {

class InputReader_test : public ::testing::Test {

 protected:
	InputReader ip;
	void SetUp() override {
		//ip.setFileName("input.ini","marketdata_for_interview_test.csv");
	}
 public:
  InputReader_test(){}
  ~InputReader_test(){}
};

}  // namespace

#endif /* INPUTREADER_TEST_H_ */

