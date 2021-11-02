//
// Created by zjh15 on 2021/11/1.
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

    Mat src,dst;
    src = imread("F:\\computer-vision\\Exp6\\city.jpg");
    if (!src.data)
    {

        cout << "could not load the image..." << endl;
        return -1;
    }
    namedWindow("input image", CV_WINDOW_AUTOSIZE);
    imshow("input image", src);

    Mat gaus,edge_image;
    GaussianBlur(src, gaus, Size(3, 3), 0, 0);
    //extract image 提取的彩色图像
    Canny(gaus, edge_image, 50, 200, 3, false); //边缘检测

    cvtColor(edge_image, dst, CV_GRAY2BGR);//转换为彩色图像

    imshow("edge_image", edge_image);

    //创建一个包含4个float元素的数组
    vector<Vec4f> plines;
    //Hough直变换
    HoughLinesP(edge_image, plines,1, CV_PI / 180, 100, 0, 20); //一般不用舍弃，大于0的保留
    //将检测到的直线画出来
    Scalar color = Scalar(0, 0, 255);
    for (size_t i = 0; i < plines.size(); i++)
    {

        Vec4f hline = plines[i];
        line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);//画线
    }
    imshow("Hough line Detection", dst);

    waitKey(0);
    return 0;
}

