//
// Created by zjh15 on 2021/10/22.
//

#ifndef EXP5_TWO_PASS_H
#define EXP5_TWO_PASS_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


void icvprCcaByTwoPass(const cv::Mat& _binImg, cv::Mat& _lableImg)
{
    // connected component analysis (4-component)
    // use two-pass algorithm
    // 1. first pass: label each foreground pixel with a label
    // 2. second pass: visit each labeled pixel and merge neighbor labels
    //
    // foreground pixel: _binImg(x,y) = 1
    // background pixel: _binImg(x,y) = 0


    if (_binImg.empty() ||
        _binImg.type() != CV_8UC1)
    {
        return ;
    }

    // 1. first pass

    _lableImg.release() ;
    _binImg.convertTo(_lableImg, CV_32SC1) ;

    int label = 1 ;  // start by 2
    std::vector<int> labelSet ;
    labelSet.push_back(0) ;   // background: 0
    labelSet.push_back(1) ;   // foreground: 1

    int rows = _binImg.rows - 1 ;
    int cols = _binImg.cols - 1 ;
    for (int i = 1; i < rows; i++)
    {
        int* data_preRow = _lableImg.ptr<int>(i-1) ;
        int* data_curRow = _lableImg.ptr<int>(i) ;
        for (int j = 1; j < cols; j++)
        {
            if (data_curRow[j] == 1)
            {// 若当前像素值为1，则将8邻域中的最小label值赋值给当前像素
                std::vector<int> neighborLabels ;
                // 建立容量为4的邻域
                neighborLabels.reserve(4) ;
                int leftPixel = data_curRow[j-1] ;
                int upLeftPixel = data_preRow[j-1] ;
                int upPixel = data_preRow[j];
                int upRightPixel = data_preRow[j+1];
                if ( leftPixel > 1)
                {
                    neighborLabels.push_back(leftPixel) ;
                }
                if (upLeftPixel > 1)
                {
                    neighborLabels.push_back(upLeftPixel) ;
                }
                if ( upPixel > 1)
                {
                    neighborLabels.push_back(upPixel) ;
                }
                if (upRightPixel > 1)
                {
                    neighborLabels.push_back(upRightPixel) ;
                }

                if (neighborLabels.empty())
                {
                    labelSet.push_back(++label) ;  // assign to a new label
                    data_curRow[j] = label ;
                    labelSet[label] = label ;
                }
                else
                {
                    std::sort(neighborLabels.begin(), neighborLabels.end()) ;
                    int smallestLabel = neighborLabels[0] ;
                    data_curRow[j] = smallestLabel ;

                    // save equivalence
                    for (size_t k = 1; k < neighborLabels.size(); k++)
                    {
                        int tempLabel = neighborLabels[k] ;
                        int& oldSmallestLabel = labelSet[tempLabel] ;
                        if (oldSmallestLabel > smallestLabel)
                        {
                            labelSet[oldSmallestLabel] = smallestLabel ;
                            oldSmallestLabel = smallestLabel ;
                        }
                        else if (oldSmallestLabel < smallestLabel)
                        {
                            labelSet[smallestLabel] = oldSmallestLabel ;
                        }
                    }
                }
            }
        }
    }

    // update equivalent labels
    // assigned with the smallest label in each equivalent label set
    for (size_t i = 2; i < labelSet.size(); i++)
    {
        int curLabel = labelSet[i] ;
        int preLabel = labelSet[curLabel] ;
        while (preLabel != curLabel)
        {
            curLabel = preLabel ;
            preLabel = labelSet[preLabel] ;
        }
        labelSet[i] = curLabel ;
    }


    // 2. second pass
    for (int i = 0; i < rows; i++)
    {
        int* data = _lableImg.ptr<int>(i) ;
        for (int j = 0; j < cols; j++)
        {
            int& pixelLabel = data[j] ;
            pixelLabel = labelSet[pixelLabel] ;
        }
    }
}

#endif //EXP5_TWO_PASS_H
