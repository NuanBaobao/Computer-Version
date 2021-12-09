//
// Created by 张进华 on 2021/11/29.
//
// 功能介绍：基于OpenCV Stitcher类进行图像拼接
// 特点：图像需有足够重合相同特征区域
// 优点：适应部分倾斜/尺度变换和畸变情形，拼接效果好，使用简单
// 缺点：需要有足够的相同特征区域进行匹配，速度较慢(和图像大小有关，可以使用GPU加速)

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    std::vector<cv::Mat> src_imgs;
    cv::Mat image1, image2, image3,image4, result_img;

    image1 = imread("F:\\computer-vision\\Exp10\\images\\6_1.jpg");
    image2 = imread("F:\\computer-vision\\Exp10\\images\\6_2.jpg");
    image3 = imread("F:\\computer-vision\\Exp10\\images\\5_3.jpg");
    image4 = imread("F:\\computer-vision\\Exp10\\images\\5_4.jpg");

    cv::namedWindow("Src_Image1",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Src_Image2",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Src_Image3",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Src_Image4",CV_WINDOW_AUTOSIZE);

    cv::imshow("Src_Image1", image1);
    cv::imshow("Src_Image2", image2);
    cv::imshow("Src_Image3", image3);
    cv::imshow("Src_Image4", image4);


    src_imgs.push_back(image1);
    src_imgs.push_back(image2);
    src_imgs.push_back(image3);
    src_imgs.push_back(image4);

    cv::Stitcher stitcher = cv::Stitcher::createDefault(); //调用create方法
    unsigned long start_time = 0, end_time = 0; // 处理时间
    start_time = cv::getTickCount(); // 开始时间

    // 使用stitch函数进行拼接
    cv::Stitcher::Status status = stitcher.stitch(src_imgs, result_img);
    end_time = cv::getTickCount(); // 结束时间
    printf("Time consuming: %.2lf sec \n", (end_time - start_time) / cv::getTickFrequency());

    if (cv::Stitcher::OK == status)
        cv::imshow("Stitching Result", result_img);    // 显示结果图像
    else
        printf("Stitching fail.");

    waitKey(0);
}
