#include "gtest/gtest.h"
#include "splitwebp.h"

TEST(splitwebp, existsInputFile_invalid) {
    splitwebp::SplitWebP splitWebP = splitwebp::SplitWebP("/dev/$$$/^^^");
    ASSERT_TRUE(!splitWebP.existsInputFile());
}

TEST(splitwebp, setInputFile_normal) {
    splitwebp::SplitWebP splitWebP = splitwebp::SplitWebP("__default");
    ASSERT_TRUE(splitWebP.setInputFile("test"));
    ASSERT_EQ(splitWebP.getInputFileName(), "test");
}

TEST(splitwebp, setInputFile_empty) {
    splitwebp::SplitWebP splitWebP = splitwebp::SplitWebP("__default");

    testing::internal::CaptureStderr();
    ASSERT_TRUE(!splitWebP.setInputFile(""));
    ASSERT_EQ(splitWebP.getInputFileName(), "");

    ASSERT_EQ(testing::internal::GetCapturedStderr(), 
        "[ERROR : Input File Name is null ]\n");
}

TEST(splitwebp, load_invalid) {
    splitwebp::SplitWebP splitWebP = splitwebp::SplitWebP("/dev/$$$/^^^");
    
    testing::internal::CaptureStderr();
    splitWebP.load();
    ASSERT_EQ(testing::internal::GetCapturedStderr(), 
        "[ERROR : Input file does not exist. ]\n");
}