//
// Created by 张进华 on 2021/11/29.
//
// 功能介绍：用于将两张图片拼接成一张大图(以左右拼接为例)，俗称的硬拼方法
// 特点：简单粗暴，现实应用对拍摄条件要求苛刻，适用性差

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img1 = imread("F:\\computer-vision\\Exp10\\images\\1.png");
    Mat img2 = imread("F:\\computer-vision\\Exp10\\images\\2.png");

    namedWindow("src1",CV_WINDOW_AUTOSIZE);
    namedWindow("src2",CV_WINDOW_AUTOSIZE);

    imshow("src1", img1);
    imshow("src2", img2);
    int w1 = img1.cols; int h1 = img1.rows;
    int w2 = img2.cols; int h2 = img2.rows;
    int width = w1 + w2; int height = max(h1, h2);
    Mat  resultImg = Mat(height, width, CV_8UC3, Scalar::all(0));
    Mat ROI_1 = resultImg(Rect(0, 0, w1, h1));
    Mat ROI_2 = resultImg(Rect(w1, 0, w2, h2));
    img1.copyTo(ROI_1);
    img2.copyTo(ROI_2);
    namedWindow("result",CV_WINDOW_AUTOSIZE);
    imshow("result", resultImg);
    waitKey(0);
    return 0;
}