
/*
 * InputReader_test.cpp
 *
 *  Created on: 02-Jun-2019
 *      Author: prashant
 */

#include <MetricCalulator.h>
#include <tickerInfo.h>
#include "InputReader_test.h"


TEST_F(InputReader_test, testEmptyFileName) {

	InputReader ip;
	EXPECT_EQ(static_cast<size_t>(1), ip.readIoSpecifiers(""));
}

TEST_F(InputReader_test, testMetricCount) {

	EXPECT_EQ(static_cast<size_t>(0), ip.readIoSpecifiers("input.ini"));
    //EXPECT_EQ(static_cast<size_t>(7),ip.readInputSpecifier().size());
}

TEST_F(InputReader_test, fileReadSuccess) {
	EXPECT_EQ(static_cast<size_t>(0), ip.readIoSpecifiers("input.ini"));
	EXPECT_EQ(static_cast<size_t>(0), ip.readRecords("marketdata_for_interview_test.csv"));
}


TEST_F(InputReader_test, verifyTickerInfo) {
	EXPECT_EQ(static_cast<size_t>(0), ip.readIoSpecifiers("input.ini"));
	EXPECT_EQ(static_cast<size_t>(0), ip.readRecords("marketdata_for_interview_test.csv"));
	auto tInfo = ip.getTickerInfo();

	auto it = tInfo.find("BC");
	GTEST_ASSERT_NE(it,tInfo.end());
	EXPECT_NEAR(tInfo.at("BC").pvDiffOfAskAndBid->at(0),1.42,0.0001);
	EXPECT_EQ(tInfo.at("BC").pvVolume->at(0),14);
	EXPECT_EQ(tInfo.at("BC").pvTimeDiffBtwnTicker->at(0),15051426);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvBidRatioNumerator->at(0),1882.08);
	EXPECT_EQ(tInfo.at("BC").pvBidRatioDenominator->at(0),24);

	EXPECT_NEAR(tInfo.at("BC").pvDiffOfAskAndBid->at(1),9.23,0.0001);
	EXPECT_EQ(tInfo.at("BC").pvVolume->at(1),13);
	EXPECT_EQ(tInfo.at("BC").pvTimeDiffBtwnTicker->at(1),1);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvBidRatioNumerator->at(1),2162.3);
	EXPECT_EQ(tInfo.at("BC").pvBidRatioDenominator->at(1),23);

	EXPECT_NEAR(tInfo.at("BC").pvDiffOfAskAndBid->at(2),3.12,0.0001);
	EXPECT_EQ(tInfo.at("BC").pvVolume->at(2),11);
	EXPECT_EQ(tInfo.at("BC").pvTimeDiffBtwnTicker->at(2),1);
	EXPECT_FLOAT_EQ(tInfo.at("BC").pvBidRatioNumerator->at(2),2221.85);
	EXPECT_EQ(tInfo.at("BC").pvBidRatioDenominator->at(2),23);
}

TEST_F(InputReader_test, testOutputData) {
	EXPECT_EQ(static_cast<size_t>(0), ip.readIoSpecifiers("input.ini"));
	EXPECT_EQ(static_cast<size_t>(0), ip.readRecords("marketdata_for_interview_test.csv"));

	MetricCalulator mc(ip.getTickerInfo());
	mc.prepareOpTickerData();
	auto opTickerData = mc.getOpTickerData().find("BC");

	EXPECT_NEAR(opTickerData->second.maxOfBid,9.23, 0.0001);
	EXPECT_NEAR(opTickerData->second.minOfBid,1.42,0.0001);
	EXPECT_EQ(opTickerData->second.sumOfVolume,38);
	EXPECT_EQ(opTickerData->second.maxTimeDiffBtwnTicker,15051426);
	EXPECT_NEAR(opTickerData->second.bidRatio,(6266.23)/70, 0.0001);
}
