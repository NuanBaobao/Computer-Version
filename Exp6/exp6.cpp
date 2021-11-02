//
// Created by zjh15 on 2021/10/29.
//
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

const char *img_path = "F:\\computer-vision\\Exp6\\earth.jpg";

Mat src_image, gray_image, dst_image, dx, dy;
int min_radius = 30;
int max_radius = 55;
int canny_threshold1 =80;
int canny_threshold2 = 100;
int acc_threshold = 45;
int H[300][1000][1000];

void vote(int x, int y)
{ // 对图像上每个点进行投票
    if (dst_image.at<uchar>(y, x) != 0)
        for (int r = min_radius; r < max_radius; r++)
        {// 遍历半径
            for (double theta = -0.1; theta <= 0.1; theta = theta + 0.05)
            {
                int a = int(x + r * cos(atan(dy.at<float>(y, x) / dx.at<float>(y, x)) + theta));
                int b = int(y + r * sin(atan(dy.at<float>(y, x) / dx.at<float>(y, x)) + theta));
                if (a >= 0 && a < dst_image.cols && b >= 0 && b < dst_image.rows)
                {
                    H[r][a][b] += 1; // 投票
                }
            }
        }
}

vector<Vec3f> my_hough_circles()
{
    vector<Vec3f> circles;
    for (int i = 0; i < dst_image.rows; i++)
    {// 对图像上每个点投票
        for (int j = 0;j < dst_image.cols; j++) vote(j, i);
    }

    circles.clear();
    for (int r = min_radius; r < max_radius; r++)
    {// 遍历半径
        for (int i = 0; i < dst_image.rows; i++)
        {
            for (int j = 0; j < dst_image.cols; j++)
            {// 遍历图像Hough空间，判断该点是否为圆心
                if (H[r][j][i] >= acc_threshold)
                {
                  circles.push_back(Vec3f(r, j, i));
                }
            }
        }
    }
 return circles;
}

int main()
{
    ios::sync_with_stdio(false);

    //载入原始图和Mat变量定义
    src_image = imread(img_path);
    namedWindow("Oringal Image", CV_WINDOW_NORMAL);
    resizeWindow("Oringal Image", 720, 405);
    imshow("Oringal Image", src_image);

    // 转为灰度图，进行图像平滑
    cvtColor(src_image, gray_image, COLOR_RGB2GRAY);
    GaussianBlur(gray_image, gray_image, Size(9, 9), 2, 2);
    // 进行边缘检测
    Canny(gray_image, dst_image, canny_threshold1,canny_threshold2);

    namedWindow("Edge detection", CV_WINDOW_NORMAL);
    resizeWindow("Edge detection", 720, 405);
    imshow("Edge detection", dst_image);

    memset(H, 0, sizeof(H));

    //进行霍夫圆变换
    Sobel(gray_image, dx, CV_32F, 1, 0, 3);
    Sobel(gray_image, dy, CV_32F, 0, 1, 3);

    vector<Vec3f> circles;
    circles.clear();
    circles = my_hough_circles();

    cout << "The number of detected circles is " << circles.size() << endl;

    //依次在图中绘制出圆
    for (size_t i = 0; i < circles.size(); i++)
    {
        cout << "The center of the circle are (" << circles[i][1] << "," << circles[i][2] << "),Radius is " << circles[i][0] << endl;

        Point center(cvRound(circles[i][1]), cvRound(circles[i][2]));
        int radius = cvRound(circles[i][0]);
        //绘制圆心
        circle(src_image, center, 3, Scalar(0, 255, 255), -1, 8, 0);
        //绘制圆轮廓
        circle(src_image, center, radius, Scalar(0, 255, 255), 0, 8, 0);
    }

    //显示效果图
    namedWindow("Effect picture", CV_WINDOW_NORMAL);
    resizeWindow("Effect picture", 720, 405);
    imshow("Effect picture", src_image);

    waitKey(0);

    return 0;
}
