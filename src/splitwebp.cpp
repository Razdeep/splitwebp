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
#include <memory>
#include "splitwebp.h"
#include "util.h"
#include <webp/decode.h>
#include <webp/demux.h>
#include "framesexporter.h"
#include "framesexporter_PNG.h"

bool splitwebp::SplitWebP::setInputFile(const char* input_file_name) {
    mInputFileName = input_file_name;
    if (int(getInputFileName().size()) < 1) {
        splitwebp::Util::printError("Input File Name is null");
        return false;
    }
    return true;
}

std::string splitwebp::SplitWebP::getInputFileName() const {
    return mInputFileName;
}

bool splitwebp::SplitWebP::existsInputFile() const {
    std::fstream fs(mInputFileName, std::ios::in | std::ios::binary);
    bool res = fs.good();
    fs.close();
    return res;
}

bool splitwebp::SplitWebP::load() {
    if (!existsInputFile()) {
        splitwebp::Util::printError("Input file does not exist.");
        return false;
    }
    std::fstream fs(mInputFileName, std::ios::in | std::ios::binary);
    auto fs_start_pos = fs.tellg();
    fs.seekg(0, std::ios::end);
    auto fs_end_pos   = fs.tellg();
    size_t file_size  = fs_end_pos - fs_start_pos;
    char *file_contents = new char[file_size];
    fs.seekg(0, std::ios::beg);
    fs.read(file_contents, file_size);
    fs.close();

    WebPData *webPData    = new WebPData();
    webPData->bytes       = (uint8_t*)(file_contents);
    webPData->size        = file_size;

    WebPDemuxer* demux = WebPDemux(webPData);

    if (demux == nullptr) {
        splitwebp::Util::printError("Webp parsing error");
        return false;
    }

    uint32_t video_height = WebPDemuxGetI(demux, WEBP_FF_CANVAS_WIDTH);
    uint32_t video_width  = WebPDemuxGetI(demux, WEBP_FF_CANVAS_HEIGHT);
    uint32_t webp_flags   = WebPDemuxGetI(demux, WEBP_FF_FORMAT_FLAGS);

    if ((webp_flags & ANIMATION_FLAG) == 0) {
        splitwebp::Util::printError("Input is not Animation");
        return false;
    }

    WebPIterator current_frame_iter;

    if (WebPDemuxGetFrame(demux, 1, &current_frame_iter)) {
        do {
            int frame_height    = current_frame_iter.height;
            int frame_width     = current_frame_iter.width;
            int x_offset        = current_frame_iter.x_offset;
            int y_offset        = current_frame_iter.y_offset;
            uint8_t* current_decoded_frame = WebPDecodeBGRA(current_frame_iter.fragment.bytes,
                                                            current_frame_iter.fragment.size,
                                                            &frame_width, &frame_height);

            if (current_decoded_frame == nullptr) {
                splitwebp::Util::printError("Animation frame is corrupted");
                return false;
            }

            cv::Mat current_frame_mat(frame_height, frame_width, CV_8UC4, current_decoded_frame);
            cv::Mat padded_current_frame_mat = current_frame_mat;
            int top_border    = y_offset;
            int bottom_border = video_height - frame_height - y_offset;
            int left_border   = x_offset;
            int right_border  = video_width - frame_width - x_offset;
            cv::copyMakeBorder(current_frame_mat, padded_current_frame_mat,
                               top_border, bottom_border,
                               left_border, right_border,
                               cv::BORDER_CONSTANT,
                               cv::Scalar(0, 0, 0, 0));

            cv::Mat grey_current_frame = cv::Mat::zeros(video_height, video_width, CV_8UC4);
            cv::cvtColor(padded_current_frame_mat, grey_current_frame, cv::COLOR_BGR2GRAY);
            cv::Mat mask = cv::Mat::zeros(video_height, video_width, CV_8UC4);
            cv::threshold(grey_current_frame, mask, 1, 255, cv::THRESH_BINARY);
            cv::Mat inversed_mask = cv::Mat::zeros(video_height, video_width, CV_8UC4);
            cv::bitwise_not(mask, inversed_mask);
            cv::Mat foreground_current_frame = cv::Mat::zeros(video_height, video_width, CV_8UC4);
            cv::bitwise_and(padded_current_frame_mat, padded_current_frame_mat, foreground_current_frame, mask);
            cv::Mat background_current_frame = cv::Mat::zeros(video_height, video_width, CV_8UC4);
            if (int(mFrameList.size())) {
                cv::Mat previous_frame = mFrameList[int(mFrameList.size()) - 1];
                cv::bitwise_and(previous_frame, previous_frame, background_current_frame, inversed_mask);
            }
            cv::Mat processed_current_frame = cv::Mat::zeros(video_height, video_width, CV_8UC4);
            cv::add(foreground_current_frame, background_current_frame, processed_current_frame);
            mFrameList.push_back(processed_current_frame);
        } while (WebPDemuxNextFrame(&current_frame_iter));

        WebPDemuxReleaseIterator(&current_frame_iter);
    } else {
        splitwebp::Util::printError("WebP file has no frames");
        return false;
    }

    WebPDemuxDelete(demux);
    return true;
}

bool splitwebp::SplitWebP::produce() const {
    std::shared_ptr<FramesExporter> frame_exporter = std::make_shared<FrameExporter_PNG>();
    frame_exporter->loadFrames(mFrameList);
    std::string outputFilePrefix = mInputFileName.substr(0, mInputFileName.find('.'));
    frame_exporter->setOutputFilePrefix(outputFilePrefix);
    frame_exporter->exportFrames();
    return true;
}