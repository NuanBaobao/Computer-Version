//
// Created by zjh on 2021/11/19.
//

#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;
const char *src_img_path = "F:\\computer-vision\\Exp9\\images\\doraemon3.jpg";
const char *template_img_path = "F:\\computer-vision\\Exp9\\images\\doraemon3-3.jpg";

int main()
{
    //加载源图像和模板图像
    cv::Mat image_source = cv::imread(src_img_path);
    cv::Mat image_template = cv::imread(template_img_path);

    // 灰度变换
    cv::Mat gray_image_source, gray_image_template;
    cv::cvtColor(image_source, gray_image_source, CV_BGR2GRAY);
    cv::cvtColor(image_template, gray_image_template,CV_BGR2GRAY);

    cv::Mat image_matched; int method;
    cout << "please choose,cv::TM_CCOEFF_NORMED is 1,cv::TM_SQDIFF is 0" << endl;
    cout << "method:";
    cin >> method;

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::Mat image_color = image_source;

    if(method == 1){
        //模板匹配
        cv::matchTemplate(gray_image_source, gray_image_template, image_matched, cv::TM_CCOEFF_NORMED);
        //寻找最佳匹配位置
        cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);

        cv::circle(image_color,
                   cv::Point(maxLoc.x + image_template.cols/2, maxLoc.y + image_template.rows/2),
                   30,
                   cv::Scalar(0, 0, 255),
                   2,
                   8,
                   0);
    }
    else{
        //模板匹配
        cv::matchTemplate(gray_image_source, gray_image_template, image_matched, cv::TM_SQDIFF);
        //寻找最佳匹配位置
        cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);

        cv::circle(image_color,
                   cv::Point(minLoc.x + image_template.cols/2, minLoc.y + image_template.rows/2),
                   30,
                   cv::Scalar(0, 0, 255),
                   2,
                   8,
                   0);
    }
//    cv::namedWindow("Template Image",WINDOW_KEEPRATIO);
    cv::imshow("Template Image", image_template);
    cv::imshow("Match Result", image_matched);
    cv::imshow("Effect Image", image_color);
    cv::waitKey(0);

    return 0;
}