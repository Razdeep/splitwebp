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
 */

#include <iostream>
#include "splitwebp.h"
#include "util.h"

bool splitwebp::SplitWebP::setInputFile(const char* input_file_name) {
    this->input_file_name = input_file_name;
    if (int(getInputFile().size()) < 1) {
        splitwebp::Util::printError("Input File Name is null");
        return false;
    }
    return true;
}

std::string splitwebp::SplitWebP::getInputFile() const {
    return input_file_name;
}

bool splitwebp::SplitWebP::checkFileExistence() const {
    return false; // @TODO Implement
}

bool splitwebp::SplitWebP::load() {
    return false; // @TODO Implement
}

bool splitwebp::SplitWebP::produce() const {
    return false; // @TODO Implement
}