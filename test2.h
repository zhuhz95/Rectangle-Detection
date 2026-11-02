#ifndef TEST2_H
#define TEST2_H

#include <iostream>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <vector>

std::vector<std::vector<cv::Point>> detectRectangles(const cv::Mat& src);

#endif