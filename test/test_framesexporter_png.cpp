#include "gtest/gtest.h"
#include "framesexporter_PNG.h"

TEST(framesexporter_png, exportFrames_init) {
    splitwebp::FrameExporter_PNG fe = splitwebp::FrameExporter_PNG();
    ASSERT_EQ(fe.getOutputFileExtension(), "png");
}