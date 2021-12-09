# 姓名学号

- 张进华 201900150221

# 实验题目

- 图像匹配3

# 实验内容

- **实验10.1 图像拼接**
  - 基于OpenCV实现图像拼接，可以对两张或更多的输入图像，将图像对齐后拼接成一张全景图。对影响拼接效果的各种因素（特征匹配、相机位移、场景几何等）拍摄图像进行测试。
- [计算机视觉——利用RANSAC实现全景图像拼接](https://blog.csdn.net/weixin_44525231/article/details/105065477?spm=1001.2014.3001.5501)
- [图像拼接处理](https://www.cnblogs.com/cenyan/p/12557065.html)
- [图像拼接边缘鬼影和结构破坏抑制方法研究](http://www.doc88.com/p-90299810940515.html)
- [RANSAC算法理解](https://blog.csdn.net/robinhjwy/article/details/79174914)

# 实验原理

#### 图像拼接

- 图像拼接是将两张或两张以上、且两两图像之间具有相同的特征点（SIFT特征点）的图像通过特征匹配拼接在一起。手机上照相机的全景照相就是图像拼接的一个应用

- 特征点匹配
  匹配错误的特征点干扰
  在进行图像匹配之前都需要找出输入的两张图片（或者多张）的特征点（SIFT特征点）然后再匹配上这些特征点，但是这可能会出现一个问题，如果图像的噪声太大，就会使得特征点的匹配发生了偏差，匹配到了错误的点，这种不好的匹配效果，会对后面的图像拼接产生很大的影响

- 消除干扰

  要消除特征点的噪声，我们可以拟合特征点，找到一个合适的拟合线，然后消除噪声点，拟合方法可以采用直线拟合

- 处理匹配错误的特征点
  经过上面的曲线拟合方法的介绍后，对于匹配错误的特征点，我们该怎么做？
  正确的做法是不断选择一对匹配的特征点，然后计算由这对特征点确定的数学模型的inliers。当inliers达到阈值条件，拟合出了数学模型后，便计算两幅对应所有特征点的偏移量，求出偏移量的平均值，最后进行图像拼接。

- RANSAC（RANdom SAmple Consensus，随机抽样一致），它是根据一组包含局外点（异常数据）的样本数据集，计算出数据的数学模型参数，得到有效样本数据的算法。在这里换句话就是说，可以从一组包含异常匹配（匹配错误）的特征点数据集中，找到可以拟合这组数据的数学模型参数，得到正确匹配的特征点。 RANSAC目的就是找到一个单应性矩阵H，使得能够满足这个单应性矩阵的特征点最多。

  ==RANSAC用来剔除由于噪声以及错误匹配的干扰的匹配点==

- RANSAC算法的步骤

  - 选择4对匹配特征点（选择4对特征点因为单应性矩阵有8个自由度，需要4个特征点，每个特征点都能构造2个方程，然后求解单应性矩阵，但是任意3个点或4个点不能在同一条直线上）
  - 根据直接线性变换解法DLT计算单应性矩阵H
  - 对所匹配点，计算映射误差
  - 根据误差阈值，确定inliers数量
  - 针对最大的inliers集合，重新计算单应性矩阵H


- 使用RANSAC图片匹配


- APAP

  APAP用来解决在图像拼接融合的过程中，受客观因素的影响，拼接融合后的图像可能会存在“鬼影现象”以及图像间过度不连续等问题

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



​     

### 3.基于特征匹配的图像拼接

  - 
  - 用SIFT算法来实现图像拼接是很常用的方法，但是因为SIFT计算量很大，所以在速度要求很高的场合下不再适用。所以，它的改进方法SURF因为在速度方面有了明显的提高（速度是SIFT的3倍），所以在图像拼接领域还是大有作为。虽说SURF精确度和稳定性不及SIFT，但是其综合能力还是优越一些。SURF要求图像有足够重合相同特征区域，且待拼接图像之间无明显尺度变换和畸变。
  - 优点：适应部分倾斜变化情况。缺点：需要有足够的相同特征区域进行匹配，速度较慢，拼接较大图片容易崩溃。下面将详细介绍拼接的主要步骤







