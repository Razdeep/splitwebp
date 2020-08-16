/**
 * MIT License
 *
 * Copyright (c) 2020 Rajdeep Roy Chowdhury
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef SPLITWEBP_SPLITWEBP_H
#define SPLITWEBP_SPLITWEBP_H

#include <opencv2/opencv.hpp>

namespace splitwebp {
    class SplitWebP {
        std::string mInputFileName = "";
        uint8_t* mEncodedData = nullptr;
        std::vector<cv::Mat> mFrameList;
    public:
        explicit SplitWebP() = delete;
        explicit SplitWebP(const char * input_file_name): mInputFileName(input_file_name) {}
        bool setInputFile(const char *);
        std::string getInputFileName() const;
        bool existsInputFile() const;
        bool load();
        bool produce() const;
    };
}
#endif //SPLITWEBP_SPLITWEBP_H
