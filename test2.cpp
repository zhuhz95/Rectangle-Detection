#include "test2.h"

std::vector<std::vector<cv::Point>> detectRectangles(const cv::Mat& src)
{
    std::vector<std::vector<cv::Point>> result;
    if (src.empty())
    {
        return result;
    }

    cv::Mat gray;
    cv::Mat edge;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::Canny(gray, edge, 50, 150);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(edge, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& cnt : contours)
    {
        std::vector<cv::Point> approx;
        double eps = cv::arcLength(cnt, true) * 0.02;
        cv::approxPolyDP(cnt, approx, eps, true);
        if (approx.size() == 4)
        {
            result.push_back(approx);
        }
    }
    return result;
}

void drawAndSaveRect(const cv::Mat& src, const std::vector<std::vector<cv::Point>>& rectList, const std::string& outFilePath)
{
    cv::Mat drawImg = src.clone();
    for(const auto& rectPts : rectList)
    {
        cv::polylines(drawImg, rectPts, true, cv::Scalar(0,255,0), 2);
    }
    cv::imwrite(outFilePath, drawImg);
}