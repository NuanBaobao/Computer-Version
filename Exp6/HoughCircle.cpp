//
// Created by zjh15 on 2021/10/29.
//
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main()
{
    //载入原始图和Mat变量定义
    Mat srcImage = imread("F:\\computer-vision\\Exp6\\earth.jpg"); // 工程目录下应该有一张名为1.jpg的素材图
    Mat midImage, dstImage;            // 临时变量和目标图的定义

    //显示原始图
    imshow("Oringal Image", srcImage);

    //转为灰度图，进行图像平滑
    cvtColor(srcImage, midImage, CV_BGR2GRAY); //转化边缘检测后的图为灰度图
    GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

    //进行边缘检测
    Canny(midImage, dstImage, 80,100);
    namedWindow("Edge detection", CV_WINDOW_NORMAL);
    resizeWindow("Edge detection", 720, 405);
    imshow("Edge detection", dstImage);

    //进行霍夫圆变换
    vector<Vec3f> circles;
    HoughCircles(dstImage, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 30, 55);

    cout << "The number of detected circles is " << circles.size() << endl;

    //依次在图中绘制出圆
    for (size_t i = 0; i < circles.size(); i++)
    {
        cout << "The center of the circle are (" << circles[i][1] << "," << circles[i][2] << "),Radius is " << circles[i][0] << endl;
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //绘制圆心
        circle(srcImage, center, 3, Scalar(0, 255, 255), -1, 8, 0);
        //绘制圆轮廓
        circle(srcImage, center, radius, Scalar(0, 255, 255), 0, 8, 0);
    }

    //显示效果图
    imshow("Effect picture", srcImage);

    waitKey(0);

    return 0;
}
