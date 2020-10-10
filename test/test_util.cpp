#include "gtest/gtest.h"
#include "util.h"

TEST(util, printError_normal) {
    testing::internal::CaptureStderr();
    splitwebp::Util::printError("test");
    ASSERT_EQ(testing::internal::GetCapturedStderr(), "[ERROR : test ]\n");
}

TEST(util, printError_empty) {
    testing::internal::CaptureStderr();
    splitwebp::Util::printError("");
    ASSERT_EQ(testing::internal::GetCapturedStderr(), "[ERROR :  ]\n");
}