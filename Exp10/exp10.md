# 姓名学号

- 张进华 201900150221

# 实验题目

- 图像匹配3

# 实验内容

- **实验10.1 图像拼接**
  - 基于OpenCV实现图像拼接，可以对两张或更多的输入图像，将图像对齐后拼接成一张全景图。对影响拼接效果的各种因素（特征匹配、相机位移、场景几何等）拍摄图像进行测试



# 实验过程遇到的问题

  ### 1.简单的图像拼接

 - 直接拼接，简单的将两张图片合并成一张大图，发现*现实应用对拍摄条件要求苛刻，适用性差*

  ![](F:\computer-vision\Exp10\images\result_1.png)



- 实现代码关键部分如下：

  ```c++
  	int w1 = img1.cols; int h1 = img1.rows;
      int w2 = img2.cols; int h2 = img2.rows;
      int width = w1 + w2; int height = max(h1, h2);
      Mat  resultImg = Mat(height, width, CV_8UC3, Scalar::all(0));
      Mat ROI_1 = resultImg(Rect(0, 0, w1, h1));
      Mat ROI_2 = resultImg(Rect(w1, 0, w2, h2));
      img1.copyTo(ROI_1);
      img2.copyTo(ROI_2);
      namedWindow("result",CV_WINDOW_AUTOSIZE);
  ```

  

### 2.基于Stitcher的图像拼接

  - Stitcher，可以将连续拍摄的图像序列，拼接成一幅全景画面，实现效果如下：

    ![](F:\computer-vision\Exp10\images\result_2.png)




  - 特点：图像需有足够重合相同特征区域

  - 优点：适应部分倾斜/尺度变换和畸变情形，拼接效果好，使用简单

  - 缺点：需要有足够的相同特征区域进行匹配，速度较慢(和图像大小有关，可以使用GPU加速)

    ```c++
    //
    // Created by 张进华 on 2021/11/29.
    //
    
    #include <iostream>
    #include <opencv2/opencv.hpp>
    
    using namespace std;
    using namespace cv;
    
    int main()
    {
        std::vector<cv::Mat> src_imgs;
        cv::Mat image1, image2, image3, result_img;
    
        src_imgs.push_back(imread("F:\\computer-vision\\Exp10\\images\\1.png"));
        src_imgs.push_back(imread("F:\\computer-vision\\Exp10\\images\\2.png"));
        src_imgs.push_back(imread("F:\\computer-vision\\Exp10\\images\\3.png"));
    
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
    ```

    

- 可以发现整个过程大概花费了1s多的时间，比较耗时 

  ![](F:\computer-vision\Exp10\images\result_3.png)

- opencv stitch选择的特征检测方式

  - 一直很好奇opencv stitch算法到底选用了哪个算法作为其特征检测方式，是ORB，SIFT还是SURF？读源码终于看到答案

    ```c++
    #ifdef HAVE_OPENCV_NONFREE
            stitcher.setFeaturesFinder(new detail::SurfFeaturesFinder());
    #else
            stitcher.setFeaturesFinder(new detail::OrbFeaturesFinder());
    #endif
    ```

    

  - 在源码createDefault函数中（默认设置），第一选择是SURF,第二选择才是ORB（没有NONFREE模块才选），所以既然大牛们这么选择，必然是经过综合考虑的，所以应该SURF算法在图像拼接有着更优秀的效果。

  

- 下面换用四张图片，采用较大的相机移位，发现最后一张图片并没有被拼接进去

  ![](F:\computer-vision\Exp10\images\result4.png)







