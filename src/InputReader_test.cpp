
/*
 * InputReader_test.cpp
 *
 *  Created on: 02-Jun-2019
 *      Author: prashant
 */

#include "InputReader_test.h"


TEST_F(InputReader_test, testEmptyFileName) {

	InputReader ip;
	EXPECT_EQ((size_t)1, ip.readInputFile());
}

TEST_F(InputReader_test, testMetricCount) {

	EXPECT_EQ((size_t)0, ip.readInputFile());
    EXPECT_EQ((size_t)7,ip.getInputRecords().size());
}

TEST_F(InputReader_test, fileReadSuccess) {
	EXPECT_EQ((size_t)0, ip.readInputFile());
	EXPECT_EQ((size_t)0, ip.readRecords());
}


TEST_F(InputReader_test, verifyTickerInfo) {
	EXPECT_EQ((size_t)0, ip.readInputFile());
	EXPECT_EQ((size_t)0, ip.readRecords());
	auto tInfo = ip.getTickerInfo();

	auto it = tInfo.find("T");
	GTEST_ASSERT_NE(it,tInfo.end());
	EXPECT_EQ(tInfo.at("T").pvTimestamp->at(0),15051426);
	EXPECT_FLOAT_EQ(tInfo.at("T").pvBid->at(0),47.46);
	EXPECT_EQ(tInfo.at("T").pvBidSize->at(0),14);
	EXPECT_FLOAT_EQ(tInfo.at("T").pvAsk->at(0),47.52);
	EXPECT_EQ(tInfo.at("T").pvAskSize->at(0),44);
	EXPECT_EQ(tInfo.at("T").pvVolume->at(0),10788);


	it = tInfo.find("BC");
	GTEST_ASSERT_NE(it,tInfo.end());
	EXPECT_EQ(tInfo.at("BC").pvTimestamp->at(0),15051426);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvBid->at(0),77.71);
	EXPECT_EQ(tInfo.at("BC").pvBidSize->at(0),12);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvAsk->at(0),79.13);
	EXPECT_EQ(tInfo.at("BC").pvAskSize->at(0),12);
	EXPECT_EQ(tInfo.at("BC").pvVolume->at(0),14);

	EXPECT_EQ(tInfo.at("BC").pvTimestamp->at(1),15051427);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvBid->at(1),90);
	EXPECT_EQ(tInfo.at("BC").pvBidSize->at(1),10);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvAsk->at(1),99.23);
	EXPECT_EQ(tInfo.at("BC").pvAskSize->at(1),13);
	EXPECT_EQ(tInfo.at("BC").pvVolume->at(1),13);

	EXPECT_EQ(tInfo.at("BC").pvTimestamp->at(2),15051428);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvBid->at(2),95.11);
	EXPECT_EQ(tInfo.at("BC").pvBidSize->at(2),11);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvAsk->at(2),98.23);
	EXPECT_EQ(tInfo.at("BC").pvAskSize->at(2),12);
	EXPECT_EQ(tInfo.at("BC").pvVolume->at(2),11);

}

