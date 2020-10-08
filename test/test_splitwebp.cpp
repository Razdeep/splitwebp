#include "gtest/gtest.h"
#include "splitwebp.h"

TEST(splitwebp, existsInputFile_invalid) {
    splitwebp::SplitWebP swp = splitwebp::SplitWebP("/dev/$$$/^^^");
    ASSERT_TRUE(!swp.existsInputFile());
}

TEST(splitwebp, setInputFile_normal) {
    splitwebp::SplitWebP swp = splitwebp::SplitWebP("__default");
    ASSERT_TRUE(swp.setInputFile("test"));
    ASSERT_EQ(swp.getInputFileName(), "test");
}

TEST(splitwebp, setInputFile_empty) {
    splitwebp::SplitWebP swp = splitwebp::SplitWebP("__default");

    testing::internal::CaptureStderr();
    ASSERT_TRUE(!swp.setInputFile(""));
    ASSERT_EQ(swp.getInputFileName(), "");

    ASSERT_EQ(testing::internal::GetCapturedStderr(), 
        "[ERROR : Input File Name is null ]\n");
}

TEST(splitwebp, load_invalid) {
    splitwebp::SplitWebP swp = splitwebp::SplitWebP("/dev/$$$/^^^");
    
    testing::internal::CaptureStderr();
    swp.load();
    ASSERT_EQ(testing::internal::GetCapturedStderr(), 
        "[ERROR : Input file does not exist. ]\n");
}