#include <opencv2/core.hpp> 
#include <opencv2/core/utility.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>  
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>  
#include <opencv2/flann.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>  
#include <stdio.h>  
#include < opencv2\opencv.hpp > 
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
	vector<Mat> imgs;
	Mat image1, image2, image3;

	image1 = imread("C:\\Users\\大狸子°\\Pictures\\X1.png");
	image2 = imread("C:\\Users\\大狸子°\\Pictures\\X2.png");
	image3 = imread("C:\\Users\\大狸子°\\Pictures\\X3.png");

	resize(image1, image1, Size(600, 450), 0, 0, INTER_LINEAR);//图片是截取的，所以使用resize做了尺寸修改
	resize(image2, image2, Size(600, 450), 0, 0, INTER_LINEAR);
	resize(image3, image3, Size(600, 450), 0, 0, INTER_LINEAR);

	imshow("原图1", image1);
	imshow("原图2", image2);
	imshow("原图3", image3);


	imgs.push_back(image1);
	imgs.push_back(image2);
	imgs.push_back(image3);

	Ptr<Stitcher> stitcher = Stitcher::create();//调用create方法
	Mat pano;
	Stitcher::Status status = stitcher->stitch(imgs, pano);	// 使用stitch函数进行拼接
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	// 显示结果图像
	imshow("全景图像", pano);
	waitKey(0);
}
