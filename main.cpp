#include <iostream>
#include <string>
#include <filesystem>
#include "test2.h"

int main()
{
    std::filesystem::path inputPath("../input");

    for (const auto& entry : std::filesystem::directory_iterator(inputPath))
    {
        std::string fullImagePath = entry.path().string();
        std::string fileName = entry.path().filename().string();

        cv::Mat src = cv::imread(fullImagePath);
        if (src.empty())
        {
            std::cout << fileName << ": 图片读取失败" << std::endl;
            continue;
        }

        std::vector<std::vector<cv::Point>> rectList = detectRectangles(src);
        int imgHeight = src.rows;

        std::cout << fileName << ":";
        if (rectList.empty())
        {
            std::cout << " null" << std::endl;
        }
        else
        {
            for (int j = 0; j < static_cast<int>(rectList.size()); j++)
            {
                const std::vector<cv::Point>& pts = rectList[j];
                std::cout << " rect" << (j + 1);

                for(int k = 0; k < 4; k++)
                {
                    int x = pts[k].x;
                    int transY = imgHeight - pts[k].y - 1;
                    std::cout << " (" << x << "," << transY << ")";
                    if(k != 3)
                    {
                        std::cout << ";";
                    }
                }
                if (j != static_cast<int>(rectList.size()) - 1)
                {
                    std::cout << " |";
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}