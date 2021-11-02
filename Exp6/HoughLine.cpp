//
// Created by zjh15 on 2021/10/29.
//

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const char *img_path = "F:\\computer-vision\\Exp6\\scany.jpg";

int main()
{
    //载入原始图和Mat变量定义
    Mat srcImage = imread(img_path, CV_8UC1);
    //显示原始图
    namedWindow("original image", 0);
    resizeWindow("original image", 900, 600);
    imshow("original image", srcImage);

    Mat dstImage; //临时变量和目标图的定义

    //进行边缘检测
    Canny(srcImage, dstImage, 10, 200, 3); //进行一此canny边缘检测
    //边缘检测后的图
    namedWindow("Image after edge detection", 0);
    resizeWindow("Image after edge detection", 900, 600);
    imshow("Image after edge detection", dstImage);

    //进行霍夫线变换
    vector<Vec2f> lines; //定义一个矢量结构lines用于存放得到的线段矢量集合
    HoughLines(dstImage, lines, 1, CV_PI / 180, 150, 0, 0);

    //依次在图中绘制出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dstImage, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
    }

    //显示效果图
    namedWindow("Effect picture", 0);
    resizeWindow("Effect picture", 900, 600);
    imshow("Effect picture", dstImage);

    waitKey(0);

    return 0;
}