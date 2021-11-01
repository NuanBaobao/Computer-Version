//
// Created by zjh15 on 2021/10/26.
//

#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char *img_path = "F:\\computer-vision\\exp5\\horse_mask.png";
const int max_len = 1e+6;

Mat img;
int parent[max_len] = {0};

int find(int x)
{
    while (parent[x] != 0)
        x = parent[x];
    return x;
}

void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        parent[x] = y;
}

Mat twoPass(Mat &srcImg)
{ // 8连通的快速连通域算法
    int rows = srcImg.rows, cols = srcImg.cols;

    Mat imgLabel = Mat::zeros(rows, cols, CV_32FC1);
    int label = 0;
    // first pass
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (srcImg.at<uchar>(y, x) != 0)
            {
                int top_left = (x - 1 < 0) || (y - 1 < 0) ? 0 : imgLabel.at<int>(y - 1, x - 1);
                int top = y - 1 < 0 ? 0 : imgLabel.at<int>(y - 1, x);
                int top_right = (y - 1 < 0) || (x + 1 > cols - 1) ? 0 : imgLabel.at<int>(y - 1, x + 1);
                int left = x - 1 < 0 ? 0 : imgLabel.at<int>(y, x - 1);

                vector<int> neighbours;
                neighbours.reserve(4);
                if (top_left > 0)
                    neighbours.emplace_back(top_left);
                if (top > 0)
                    neighbours.emplace_back(top);
                if (top_right > 0)
                    neighbours.emplace_back(top_right);
                if (left > 0)
                    neighbours.emplace_back(left);

                if (neighbours.empty())
                    imgLabel.at<int>(y, x) = ++label;
                else
                {
                    sort(neighbours.begin(), neighbours.end());
                    int minLabel = neighbours[0];
                    imgLabel.at<int>(y, x) = minLabel;
                    for (int i = 1; i < neighbours.size(); i++)
                        unite(neighbours[i], minLabel);
                }
            }
        }
    }
    // second pass
    vector<int> labelCount(label, 0); // 计数
    set<int> label_set; // 连通域个数
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (srcImg.at<uchar>(y, x) != 0)
                imgLabel.at<int>(y, x) = find(imgLabel.at<int>(y, x));
            labelCount[imgLabel.at<int>(y, x)]++;
            label_set.insert(imgLabel.at<int>(y, x));
        }
    }

    Mat temp = Mat::zeros(srcImg.size(), srcImg.type());
    auto maxLabel = max_element(labelCount.begin() + 1, labelCount.end()) - labelCount.begin();
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (imgLabel.at<int>(y, x) == maxLabel)
                temp.at<uchar>(y, x) = 255;
        }
    }

    cout << "Number of white connected regions = " << label_set.size() << endl;
    return temp;
}

Mat distanceField(Mat &srcImg)
{ // 距离场可视化
    int rows = srcImg.rows, cols = srcImg.cols;

    Mat distanceImg = Mat::zeros(rows, cols, CV_32FC1);
    distanceTransform(srcImg, distanceImg, DIST_L2, 3);

    normalize(distanceImg, distanceImg, 0, 1, NORM_MINMAX);

    return distanceImg;
}

int main()
{
    ios::sync_with_stdio(false);

    img = imread(img_path, CV_8UC1);
    cv::threshold(img, img, 127, 255, CV_THRESH_BINARY);

    namedWindow("Origin Image", WINDOW_AUTOSIZE);
    imshow("Origin Image", img);

    Mat labelImg = twoPass(img);
    namedWindow("Label Image", WINDOW_AUTOSIZE);
    imshow("Label Image", labelImg);

    Mat distanceImg = distanceField(labelImg);
    namedWindow("Distance Image", WINDOW_AUTOSIZE);
    imshow("Distance Image", distanceImg);

    waitKey(0);
    destroyAllWindows();

    return 0;
}